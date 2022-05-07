#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  char *result;
  char *start_token;
  char *end_token;
  static char *last_point = S21_NULL;

  if (str != S21_NULL) {
    last_point = str;
  }
  start_token = last_point;

  if (start_token != S21_NULL) {
    start_token += s21_strspn(start_token, delim); /* clear delim from start */
    end_token = start_token;

    if (*start_token == '\0') {
      last_point = S21_NULL;
      result = S21_NULL;
    } else {
      result = start_token;
    }

    end_token = start_token + (s21_strpbrk(start_token, delim) - start_token);
    if (end_token != S21_NULL) {
      *end_token = '\0';
      last_point = end_token + 1;
    } else {
      last_point = S21_NULL;
      result = start_token;
    }

  } else {
    last_point = S21_NULL;
    result = S21_NULL;
  }

  return result;
}