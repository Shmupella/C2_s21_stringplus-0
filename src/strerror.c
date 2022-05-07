#include "strerror.h"

char *s21_strerror(int errnum) {
  static char massError[1024];
  char *result = massError;
  if (errnum < 0 || errnum >= MAX_NUM) {
    char str[80];
    s21_sprintf(str, "%d", errnum);
    s21_strcpy(result, "Unknown error");
#if defined(__APPLE__)
    s21_strcat(result, ":");
#endif
    s21_strcat(result, " ");
    s21_strcat(result, str);
  } else {
    char *mass[MAX_NUM] = ERRLIST;
    s21_strcpy(result, mass[errnum]);
  }
  return result;
}