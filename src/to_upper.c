#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  void *tmp;
  if (str != S21_NULL) {
    int n = s21_strlen(str);
    tmp = malloc((n + 1) * sizeof(char));
    for (int i = 0; i < n; i++) {
      if ((*((char *)str + i) > 96) & (*((char *)str + i) < 123)) {
        *((char *)tmp + i) = *((char *)str + i) - 32;
      } else {
        *((char *)tmp + i) = *((char *)str + i);
      }
    }
    ((char *)tmp)[n] = '\0';
  } else {
    tmp = S21_NULL;
  }
  return (char *)tmp;
}
