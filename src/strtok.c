#include <stdio.h>
#include <string.h>

char *s21_strtok(char *str, const char *delim);

int main() {
  char arr[] = "//Em/ily";
  char del[] = "/";
  char arr2[] = "//Em/ily";
  char del2[] = "/";

  /*if (s21_strtok(arr, del) == strtok(arr2, del2)) {
      printf("First test zaebok!\n");
  } else {
      printf("First test ne zaebok!\n");
  }
  if (s21_strtok(NULL, del) == strtok(NULL, del2)) {
      printf("Secondt test zaebok!\n");
  } else {
      printf("Second test ne zaebok!\n");
  }*/
  printf("%s\n", s21_strtok(arr, del));
  printf("%s\n", s21_strtok(NULL, del));
  printf("%s\n", s21_strtok(NULL, del));
  printf("%s\n", strtok(arr2, del));
  printf("%s\n", strtok(NULL, del2));
  printf("%s\n", strtok(NULL, del2));

  return 0;
}

char *s21_strtok(char *str, const char *delim) {
  static char *p = 0;
  if (str) {
    p = str;
  } else {
    if (!p) {
      return 0;
    }
  }
  str = p + strspn(p, delim);
  p = str + strcspn(str, delim);
  if (p == str) {
    return p = 0;
  }
  /*p = *p ? * p = 0, p + 1 : 0;*/
  if (*p) {
    *p = 0;
    p = p + 1;

  } else {
    p = 0;
  }
  return str;
}
