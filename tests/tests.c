#include <stdio.h>
#include <stdlib.h>

#define __RC4_IMPLEMENTATION__
#include "../src/rc4.h"

void test(char *result, char *expected) {
  if (strcmp(expected, result)) {
    fprintf(stderr, "Expected: %s. Actual: %s.\n", expected, result);
    exit(1);
  }
}

int main(void) {
  char *e = encrypt("Secret", "Attack at dawn");
  char *d = decrypt("Secret", e);

  test(e, "45A01F645FC35B383552544B9BF5");
  test(d, "Attack at dawn");

  puts("RC4: OK");

  free(e);
  free(d);

  return 0;
}
