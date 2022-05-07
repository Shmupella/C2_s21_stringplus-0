#include "s21_string.h"

int strncmp(const char *str1, const char *str2, unsigned int n) {
  unsigned char *s1;
  unsigned char *s2;
  unsigned int i;
  s1 = (unsigned char *)str1;
  s2 = (unsigned char *)str2;
  i = 0;
  while (i < n) {
    if (s1[i] != s2[i]) {
      return (s1[i] - s2[i]);
    }
    if (s1[i] == '\0' || s2[i] == '\0') {
      return (0);
    }
    i++;
  }
  return (0);
}
