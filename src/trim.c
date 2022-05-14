#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  void *temp = S21_NULL;
  if ((trim_chars == S21_NULL) && (src != S21_NULL)) {
    temp = malloc((s21_strlen(src) + 1) * sizeof(char));
    s21_strcpy(temp, src);
  } else if (src != S21_NULL) {
    int i = 0, j = s21_strlen(src);
    while ((i < j) &&
           (s21_strchr(trim_chars, *(char *)(src + i)) != S21_NULL)) {
      i++;
    }
    while ((j - 1 > 0) &&
           (s21_strchr(trim_chars, *(char *)(src + j - 1)) != S21_NULL)) {
      j--;
    }
    temp = malloc((j - i + 2) * sizeof(char));
    s21_memcpy(temp, (char *)(src + i), j - i);
    ((char *)temp)[j - i] = '\0';
  }
  return temp;
}