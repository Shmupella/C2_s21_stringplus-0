#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  char *str;
  str = dest;
  while (*dest) {
    dest++;
  }
  while ((*dest++ = *src++)) {
    ;
  }
  return (str);
}
