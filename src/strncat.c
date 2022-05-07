#include "s21_string.h"

char *strncat(char *dest, const char *src, size_t n) {
  char *str;
  str = dest;
  while (*dest) {
    dest++;
  }
  while (n-- != 0 && (*dest++ = *src++)) {
    if (n == 0) {
      *dest = '\0';
    }
  }
  return (str);
}