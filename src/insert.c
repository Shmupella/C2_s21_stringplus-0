#include <stdlib.h>

#include "s21_string.h"

void *insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t length_str = 0;
  s21_size_t length_src = 0;
  void *tmp = s21_NULL;
  if (src && str) {
    length_src = s21_strlen(src);
    if (start_index <= length_src) {
      length_str = s21_strlen(str);
      tmp = malloc((length_src + length_str + 1) * sizeof(char));
      s21_memcpy(tmp, (char *)src, start_index);
      s21_memcpy((char *)(tmp + start_index), (char *)str, length_str);
      s21_memcpy(((char *)tmp + start_index + length_str),
                 ((char *)src + start_index), length_src - start_index);
      ((char *)tmp)[n] = '\0';
    }
  }
  return tmp;
}