#define  __RC4_IMPLEMENTATION__
#include "rc4.h"

typedef enum { ENC, DEC } Mode;

typedef struct {
  Mode mode;
  char *key;
  char *input;
} Config;

Config config(int n, char **args) {
  size_t i = 1;
  char *program = args[0];
  char *key = NULL, *input = NULL, mode = 0;

  if (n != 5) goto error;

  for (; i < n; i++) {
    if (!strcmp(args[i], "-k")) {
      if (++i < n) key = args[i];
      else goto error;
      if (strlen(key) > 256) {
        printf("Key must be less than 256 characters.\n");
        exit(1);
      }
    } else if (!strcmp(args[i], "-e")) {
      if (++i < n && mode != DEC)
        input = args[i], mode = ENC;
      else goto error;
    } else if (!strcmp(args[i], "-d")) {
      if (++i < n)
        input = args[i], mode = DEC;
      else goto error;
    } else goto error;
  }

  if (i != n) goto error;

  return (Config){ mode, key, input };

  error:
    printf("Usage: %s -k key [-e plaintext | -d ciphertext]\n", program);
    exit(1);
}

int main(int argc, char **argv) {
  Config cfg = config(argc, argv);

  char *output = cfg.mode == ENC
    ? encrypt(cfg.key, cfg.input)
    : decrypt(cfg.key, cfg.input);

  printf("%s\n", output);

  free(output);
  return 0;
}
