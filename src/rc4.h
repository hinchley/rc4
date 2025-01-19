#ifndef __RC4_H__
#define __RC4_H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define uchar unsigned char

char *encrypt(char *key, char *pt);
char *decrypt(char *key, char *ct);

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
  uchar j = 0;
  size_t i = 0, n = strlen(key);

  for (i = 0; i < 256; i++) s[i] = (uchar)i;

  for (i = 0; i < 256; i++) {
    j = (j + s[i] + key[i % n]) % 256;
    swap(s + i, s + j);
  }
}

void prga(uchar *s, uchar *input, uchar *output) {
  uchar i = 0, j = 0;

  for (size_t k = 0, n = strlen((char *)input); k < n; k++) {
    i = (i + 1) % 256;
    j = (j + s[i]) % 256;
    swap(s + i, s + j);
    uchar t = (s[i] + s[j]) % 256;
    output[k] = s[t] ^ input[k];
  }
}

uchar *rc4(char *key, uchar *input) {
  uchar s[256];
  size_t n = strlen((char *)input);
  uchar *output = allocate(n);

  ksa(key, s);
  prga(s, input, output);
  return output;
}

char *toHex(uchar *bytes) {
  size_t n = strlen((char *)bytes);
  char *hex = (char *)allocate(2 * n);

  for (size_t i = 0; i < n; i++) {
    sprintf(&hex[i * 2], "%02hhX", bytes[i]);
  }

  return hex;
}

uchar *toBytes(char *hex) {
  size_t n = strlen(hex);
  uchar *bytes = allocate(n / 2);

  for (size_t i = 0; i < n; i += 2) {
    sscanf(&hex[i], "%02hhX", &bytes[i / 2]);
  }

  return bytes;
}

char *encrypt(char *key, char *input) {
  uchar *bytes = rc4(key, (uchar *)input);
  char *hex = toHex(bytes);
  free(bytes);
  return hex;
}

char *decrypt(char *key, char *input) {
  uchar *bytes = toBytes(input);
  uchar *output = rc4(key, bytes);
  free(bytes);
  return (char *)output;
}

#endif // implementation
#endif // header
