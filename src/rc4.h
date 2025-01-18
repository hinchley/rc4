#ifndef __RC4_H__
#define __RC4_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char

void encrypt(char *key, char *pt);
void decrypt(char *key, char *ct);

#ifdef __RC4_IMPLEMENTATION__

uchar *allocate(size_t n) {
  uchar *m = (uchar *)calloc(n, sizeof(m[0]));
  if (m != NULL) return m;
  printf("Memory allocation error.\n");
  exit(1);
}

void swap(uchar *a, uchar *b) {
  char t = *a;
  *a = *b;
  *b = t;
}

void ksa(char *key, uchar *s) {
  uchar  j = 0;
  size_t i = 0, n = strlen(key);

  for (i = 0; i < 256; i++) s[i] = (uchar)i;

  for (i = 0; i < 256; i++) {
    j = (j + s[i] + key[i % n]) % 256;
    swap(s + i, s + j);
  }
}

void prga(char *s, char *input, uchar *output) {
  uchar i = 0, j = 0;

  for (size_t k = 0, n = strlen(input); k < n; k++) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(s + i, s + j);
    uchar t = (s[i] + s[j]) % 256;
    output[k] = s[t] ^ input[k];
  }
}

uchar *rc4(char *key, uchar *input) {
  uchar s[256];
  uchar *output = allocate(strlen(input));

  ksa(key, s);
  prga(s, input, output);
  return output;
}

void encrypt(char *key, char *input) {
  uchar *output = rc4(key, (uchar *)input);

  for (size_t i = 0; i < strlen(output); i++) {
    printf("%02hhX", output[i]);
  }

  printf("\n");
  free(output);
}

void decrypt(char *key, char *input) {
  size_t n = strlen(input);
  uchar *bytes = allocate(n);

  for (size_t i = 0; i < n; i += 2) {
    sscanf(input + i, "%2hhX", &bytes[i / 2]);
  }

  uchar *output = rc4(key, bytes);

  printf("%s\n", output);
  free(bytes);
  free(output);
}

#endif // implementation
#endif // header
