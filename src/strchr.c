#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  while (*str != (unsigned char)c) {
    if (*str++ == '\0') {
      return (NULL);
    }
  }
  return ((char *)str);
}