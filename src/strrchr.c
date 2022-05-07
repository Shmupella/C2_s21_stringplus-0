#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  int i;
  i = 0;
  while (str[i]) {
    i++;
  }
  while (i >= 0) {
    if (str[i] == (char)c) {
      return ((char *)str + i);
    }
    --i;
  }
  return (NULL);
}