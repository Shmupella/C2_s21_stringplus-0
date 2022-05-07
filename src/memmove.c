#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, size_t n) {
  char *d;
  char *s;
  size_t i;
  d = (char *)dest;
  s = (char *)src;
  i = -1;
  if (d < s) {
    while (++i < n) {
      d[i] = s[i];
    }
  } else {
    while ((int)(--n) >= 0) {
      d[n] = s[n];
    }
  }
  return (dest);
}