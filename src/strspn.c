#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
    int n_str1 = s21_strlen(str1);
    int flag = 1;
    s21_size_t res_len = 0;
    for (int i = 0; i < n_str1 && flag; i++) {
        if (s21_strchr(str2, (str1 + i)[0]) != S21_NULL) {
            res_len++;
        } else {
            flag = 0;
        }
    }
    return res_len;
}