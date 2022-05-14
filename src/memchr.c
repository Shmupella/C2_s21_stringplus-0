#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  unsigned char *s = (unsigned char *)str;
  while (n-- != 0) {
    if (*s == (unsigned char)c) {
      return (s);
    }
    s++;
  }
  return (NULL);
}