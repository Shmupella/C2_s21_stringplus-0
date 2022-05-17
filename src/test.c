#include <check.h>
#include <stdio.h>
#include <string.h>

#include "s21_string.h"

START_TEST(memchr_test) {
  char str[] = {65, 70, 0, 'T'};
  int c = 0;
  int n = 4;

  char str2[] = {65, 70, 0, 'T'};
  int c2 = 84;
  int n2 = 4;

  char str3[] = {65, 70, 0, 'T'};
  int c3 = 'T';
  int n3 = 4;

  char str4[] = {65, 70, 0, 'T'};
  int c4 = 0;
  int n4 = 2;

  char str5[] = "";
  int c5 = 'T';
  int n5 = 1;

  int str6[] = {1, 2, 0, 44};
  int c6 = 0;
  int n6 = 4;

  int str7[] = {1, 2, 0, 44};
  int c7 = 44;
  int n7 = 16;

  int str8[] = {1, 2, 0, 999};
  int c8 = 999;
  int n8 = 16;

  ck_assert_pstr_eq(s21_memchr(str, c, n), memchr(str, c, n));
  ck_assert_pstr_eq(s21_memchr(str2, c2, n2), memchr(str2, c2, n2));
  ck_assert_pstr_eq(s21_memchr(str3, c3, n3), memchr(str3, c3, n3));
  ck_assert_pstr_eq(s21_memchr(str4, c4, n4), memchr(str4, c4, n4));
  ck_assert_pstr_eq(s21_memchr(str5, c5, n5), memchr(str5, c5, n5));
  ck_assert_pstr_eq(s21_memchr(str6, c6, n6), memchr(str6, c6, n6));
  ck_assert_pstr_eq(s21_memchr(str7, c7, n7), memchr(str7, c7, n7));
  ck_assert_pstr_eq(s21_memchr(str8, c8, n8), memchr(str8, c8, n8));
}
END_TEST

START_TEST(memcmp_test) {
  char *str1 = "";
  char *str2 = "1237";
  int n = 4;

  char *str3 = "Emily";
  char *str4 = "Emil";
  int n2 = 3;

  int str5[] = {1, 9, 5, 44};
  int str6[] = {1, 9, 5, 44};
  int n3 = 3;

  char str7[] = {'A', 'B', 67};
  char str8[] = "";
  int n4 = 1;

  char *str9 = "1237";
  char *str10 = "1237";
  int n5 = 0;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
  ck_assert_int_eq(s21_memcmp(str3, str4, n2), memcmp(str3, str4, n2));
  ck_assert_int_eq(s21_memcmp(str5, str6, n3), memcmp(str5, str6, n3));
  ck_assert_int_eq(s21_memcmp(str7, str8, n4), memcmp(str7, str8, n4));
  ck_assert_int_eq(s21_memcmp(str9, str10, n5), memcmp(str9, str10, n5));
}
END_TEST

START_TEST(memcpy_test) {
  int dest1[] = {56, 999, 90, 14};
  int dest21[] = {56, 999, 23, 14};
  int src1[] = {90, 28, 56, 0};
  int n1 = 16;

  ck_assert_mem_eq(s21_memcpy(dest21, src1, n1), memcpy(dest1, src1, n1), n1);
}
END_TEST

START_TEST(memmove_test) {
  char src1[] = "Emily love.";
  char src2[] = "Emily love.";
  int n = 5;
  ck_assert_mem_eq(s21_memmove(&src1[3], src1, n), memmove(&src2[3], src2, n),
                   6);
}
END_TEST

START_TEST(memset_test) {
  int m1[] = {56, 999, -4, 5};
  int m2[] = {56, 999, -4, 5};
  int c1 = '!';
  int n1 = 16;

  char dest[] = "Hello";
  char dest21[] = "Hello";
  int c2 = '!';
  int n2 = 5;

  ck_assert_mem_eq(memset(m1, c1, n1), s21_memset(m2, c1, n1), n1);
  ck_assert_mem_eq(memset(dest, c2, n2), s21_memset(dest21, c2, n2), n2);
}
END_TEST

START_TEST(strcat_test) {
  char dest[15] = "Hello";
  char append[] = "Emily";
  char append1[] = "";
  char s21_dest[15] = "Hello";

  ck_assert_mem_eq(strcat(dest, append), s21_strcat(s21_dest, append), 6);
  ck_assert_mem_eq(strcat(dest, append1), s21_strcat(s21_dest, append1), 6);
}
END_TEST

START_TEST(strncat_test) {
  char dest[9] = "Hello";
  char append[] = "Emily";
  char s21_dest[15] = "Hello";
  int n = 3;

  ck_assert_str_eq(strncat(dest, append, n), s21_strncat(s21_dest, append, n));
}
END_TEST

START_TEST(strchr_test) {
  char *str = "Emily";
  int ch = 'y';
  char str2[] = "";
  int ch2 = '!';
  ck_assert_pstr_eq(strchr(str, ch), s21_strchr(str, ch));
  ck_assert_pstr_eq(strchr(str2, ch2), s21_strchr(str2, ch2));
}
END_TEST

START_TEST(strcmp_test) {
  char str1[] = "Hello";
  char str2[] = "Emily";
  char str3[] = "";
  char str4[] = "Emily";
  char str5[] = "Hello";
  char str6[] = "Yoy";
  char str7[] = "Wiz\n";
  char str8[] = "Wi\n";

  ck_assert_int_eq(strcmp(str1, str2), s21_strcmp(str1, str2));
  ck_assert_int_eq(strcmp(str3, str4), s21_strcmp(str3, str4));
  ck_assert_int_eq(strcmp(str5, str6), s21_strcmp(str5, str6));
  ck_assert_int_eq(strcmp(str7, str8), s21_strcmp(str7, str8));
}
END_TEST

START_TEST(strncmp_test) {
  char str1[] = "Hello";
  char str2[] = "Emily";
  char str3[] = "";
  char str4[] = "Emily";
  char str5[] = "Hello";
  char str6[] = "Yoy";
  char str7[] = "Wiz\n";
  char str8[] = "Wi\n";
  char str9[] = "Emily";
  char str10[] = "";
  int n1 = 5;
  int n2 = 1;
  int n3 = 2;
  int n4 = 2;
  int n5 = 3;

  ck_assert_int_eq(s21_strncmp(str1, str2, n1), strncmp(str1, str2, n1));
  ck_assert_int_eq(s21_strncmp(str3, str4, n2), strncmp(str3, str4, n2));
  ck_assert_int_eq(s21_strncmp(str5, str6, n3), strncmp(str5, str6, n3));
  ck_assert_int_eq(s21_strncmp(str7, str8, n4), strncmp(str7, str8, n4));
  ck_assert_int_eq(s21_strncmp(str7, str8, n5), strncmp(str7, str8, n5));
  ck_assert_int_eq(s21_strncmp(str9, str10, n2), strncmp(str9, str10, n2));
}
END_TEST

START_TEST(strcpy_test) {
  char s21_dest1[] = "Emily";
  char src1[] = "";
  char dest1[] = "Emily";
  char s21_dest2[] = "!privet\n";
  char dest2[] = "!privet\n";
  char src2[] = "12";
  char s21_dest3[6];
  char dest3[6];
  char src3[] = "1203";

  ck_assert_str_eq(s21_strcpy(s21_dest1, src1), strcpy(dest1, src1));
  ck_assert_str_eq(s21_strcpy(s21_dest2, src2), strcpy(dest2, src2));
  ck_assert_str_eq(s21_strcpy(s21_dest3, src3), strcpy(dest3, src3));
}
END_TEST

START_TEST(strncpy_test) {
  char s21_dest[10] = "!Emily";
  char append[] = "haha";
  char dest[10] = "!Emily";
  int n = 4;

  char s21_dest1[] = "Emily";
  char src1[] = "";
  char dest1[] = "Emily";
  int n2 = 5;

  ck_assert_str_eq(s21_strncpy(s21_dest, append, n), strncpy(dest, append, n));
  ck_assert_str_eq(s21_strncpy(s21_dest1, src1, n2), strncpy(dest1, src1, n2));
}
END_TEST

START_TEST(strcspn_test) {
  char s1[] = "Emily/ha/ha";
  char delim[] = "/";

  ck_assert_uint_eq(s21_strcspn(s1, delim), strcspn(s1, delim));
}
END_TEST

START_TEST(strerror_test) {
  for (int i = -2; i < 136; i++) {
    ck_assert_str_eq(s21_strerror(i), strerror(i));
  }
}
END_TEST

START_TEST(strlen_test) {
  char str[] = "Emily";
  char *str2 = "";

  ck_assert_uint_eq(strlen(str), s21_strlen(str));
  ck_assert_uint_eq(strlen(str2), s21_strlen(str2));
}
END_TEST

START_TEST(strpbrk_test) {
  char *str1 = "01234567";
  char *str2 = "9I";
  char *str3 = "hi\n";
  char *str4 = "4\n";

  ck_assert_ptr_eq(s21_strpbrk(str1, str2), strpbrk(str1, str2));
  ck_assert_ptr_eq(s21_strpbrk(str3, str4), strpbrk(str3, str4));
}
END_TEST

START_TEST(strrchr_test) {
  char *str1 = "012345672";
  int c = '2';
  char *str2 = "\n!Z";
  char *str3 = "Emily";
  int c2 = 0;
  char *str4 = "";
  int c3 = 65;

  ck_assert_ptr_eq(s21_strrchr(str1, c), strrchr(str1, c));
  ck_assert_ptr_eq(s21_strrchr(str2, c), strrchr(str2, c));
  ck_assert_ptr_eq(s21_strrchr(str3, c2), strrchr(str3, c2));
  ck_assert_ptr_eq(s21_strrchr(str4, c3), strrchr(str4, c3));
}
END_TEST

START_TEST(strspn_test) {
  char s1[] = "///Emily/ha/ha";
  char delim[] = "/";
  ck_assert_uint_eq(s21_strspn(s1, delim), strspn(s1, delim));
}
END_TEST

START_TEST(strstr_test) {
  char *str1 = "Foo Bar Baz";
  char *str2 = "Bar";
  char *str3 = "Foo Bar Baz";
  char *str4 = "";
  char *str5 = "Foo Bar Baz";
  char *str6 = "\n!YZ";

  ck_assert_ptr_eq(s21_strstr(str1, str2), strstr(str1, str2));
  ck_assert_ptr_eq(s21_strstr(str3, str4), strstr(str3, str4));
  ck_assert_ptr_eq(s21_strstr(str5, str6), strstr(str5, str6));
}
END_TEST

START_TEST(strtok_test) {
  char s1[] = "///Emily/ha/ha";
  char s2[] = "///Emily/ha/ha";
  char delim[] = "/";
  char *part = strtok(s1, delim);
  char *s21_part = s21_strtok(s2, delim);
  ck_assert_str_eq(part, s21_part);
  while (part) {
    part = strtok(NULL, delim);
    s21_part = s21_strtok(s21_NULL, delim);
    if (part) {
      ck_assert_str_eq(part, s21_part);
    } else {
      ck_assert_ptr_null(s21_part);
    }
  }
}
END_TEST

START_TEST(to_upper_test) {
  char *str1 = "Emilia - is the fUcKiNg pretty Girl!";
  char *s21_res1 = s21_to_upper(str1);
  char *res1 = "EMILIA - IS THE FUCKING PRETTY GIRL!";
  ck_assert_pstr_eq(s21_res1, res1);
  free(s21_res1);

  char *str2 = "";
  char *s21_res2 = s21_to_upper(str2);
  ck_assert_pstr_eq(s21_res2, str2);
  free(s21_res2);

  char *str3 = "\n1234Hello, Mini-VerteR!";
  char *res3 = "\n1234HELLO, MINI-VERTER!";
  char *s21_res3 = s21_to_upper(str3);
  ck_assert_pstr_eq(s21_res3, res3);
  free(s21_res3);
}
END_TEST

START_TEST(to_lower_test) {
  char *str1 = "Emilia - is the fUcKiNg pretty Girl!";
  char *s21_res1 = s21_to_lower(str1);
  char *res1 = "emilia - is the fucking pretty girl!";
  ck_assert_pstr_eq(s21_res1, res1);
  free(s21_res1);

  char *str2 = "";
  char *s21_res2 = s21_to_lower(str2);
  ck_assert_pstr_eq(s21_res2, str2);
  free(s21_res2);

  char *str3 = "\n1234Hello, Mini-VerteR!";
  char *res3 = "\n1234hello, mini-verter!";
  char *s21_res3 = s21_to_lower(str3);
  ck_assert_pstr_eq(s21_res3, res3);
  free(s21_res3);
}
END_TEST

START_TEST(insert_test) {
  char *dest1 = "Call me\n50898";
  char *src1 = " ba be !";
  char *res = "Call me ba be !\n50898";
  char *s21_res = s21_insert(dest1, src1, 7);
  ck_assert_pstr_eq(s21_res, res);
  free(s21_res);

  char *dest2 = "";
  char *src2 = " ba be !";
  char *s21_res2 = s21_insert(dest2, src2, 1);
  ck_assert_ptr_null(s21_res2);
  free(s21_res2);
}
END_TEST

START_TEST(trim_test) {
  char *res = s21_trim("testc", "c");
  ck_assert_str_eq(res, "test");
  free(res);

  res = s21_trim(" test ", " ");
  ck_assert_str_eq(res, "test");
  free(res);

  res = s21_trim(" ", " ");
  ck_assert_str_eq(res, "");
  free(res);

  res = s21_trim("*te*st*", "*");
  ck_assert_str_eq(res, "te*st");
  free(res);

  res = s21_trim(" te st001", " ");
  ck_assert_str_eq(res, "te st001");
  free(res);

  res = s21_trim(" ()", ")(/ *");
  ck_assert_str_eq(res, "");
  free(res);
}
END_TEST

START_TEST(sprintf_test) {
  char c[255] = {}, d[255] = {}, x1 = 't';
  int n = 2100, n1 = 0, n2 = -21;
  short sh = 123, sh1 = -123;
  float f = 21.21, f1 = -21.21;
  long int lg = 12345678912345, lg1 = -12345678912345;
  s21_sprintf(c, "%% %p", &n);
  sprintf(d, "%% %p", &n);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
              lg1);
  sprintf(d, "%d %d %d %hd %hd %ld %ld %10ld", n, n1, n2, sh, sh1, lg, lg1,
          lg1);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
              2121, n2, n, 21, 55, -55);
  sprintf(d, "%10d %+3d %+010d %+-10d %+-10d % -10d %-10d %-10d", n, 212121,
          2121, n2, n, 21, 55, -55);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
  sprintf(d, "%-10d %010d %010d %*d %2d", 21, n2, n, 10, n, n2);
  ck_assert_str_eq(c, d);
  s21_sprintf(c,
              "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
              10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
  sprintf(d, "%.*d %3.10d %.d %-+.5d %-+10.5d %.10d %.10d %2.2d %.d % d %.0d",
          10, n, n2, 42, 21, 10, n, n2, -21, x1, 21, -42);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
              USHRT_MAX, LONG_MAX, LONG_MIN);
  sprintf(d, "%d %d %d %d %d %ld %ld", INT_MIN, INT_MAX, SHRT_MAX, SHRT_MIN,
          USHRT_MAX, LONG_MAX, LONG_MIN);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%c %10c %-10c", '!', 'a', 'b');
  sprintf(d, "%c %10c %-10c", '!', 'a', 'b');
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
  sprintf(d, "%c %c %c", CHAR_MAX, CHAR_MIN, UCHAR_MAX);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello",
              "hello", "hello", "hello", "hello");
  sprintf(d, "%s %10s %-10s %-3s %.s %.3s %.10s", "hello", "hello", "hello",
          "hello", "hello", "hello", "hello");
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello", L"hello",
              L"hello", L"hello", L"hello", L"hello", L"hello");
  sprintf(d, "%ls %10ls %-10ls %-3ls %.ls %.3ls %.10ls", L"hello", L"hello",
          L"hello", L"hello", L"hello", L"hello", L"hello");
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%u %lu", UINT_MAX, ULONG_MAX);
  sprintf(d, "%u %lu", UINT_MAX, ULONG_MAX);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "hello %n", &n);
  sprintf(d, "hello %n", &n1);
  ck_assert_msg(c, d, "error");
  s21_sprintf(c, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0,
              n2, 0, 21, 42);
  sprintf(d, "%-10o %lo %lo %o %o %o %10o %#10o %0#10o", 21, lg, lg1, n, 0, n2,
          0, 21, 42);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0,
              123);
  sprintf(d, "%#o %#o %#10o %0#10o %.10o %.0o %#5.10o", n, n2, 0, 0, n, 0, 123);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n,
              0, 123);
  sprintf(d, "%x %x %x %10x %-10x %.10x %.0x %#5.10x", n, n1, n2, 0, 21, n, 0,
          123);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n,
              n2, 21, 0, 42, 21, 0, -65, lg, lg1);
  sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n, n2,
          21, 0, 42, 21, 0, -65, lg, lg1);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
  sprintf(d, "%X %X %X %10X %-10X %lX", n, n1, n2, 0, 21, lg1);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0,
              4221, n1);
  sprintf(d, "%#X %#X %-#10X %#10X %#10X %0#10X %0#10X", n, n2, 21, 42, 0, 4221,
          n1);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1,
              21.21, -21.21, 42.42, -42.42, f, f1);
  sprintf(d, "%+.1f %.2f %.3f %.4f %10.5f %10.5f %-10.3f %-10.2f", f, f1, 21.21,
          -21.21, 42.42, -42.42, f, f1);
  ck_assert_str_eq(c, d);
  s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
              21.21, 0.0, 21.21, 21., 0.0, 21.21);
  sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21., 21.21,
          0.0, 21.21, 21., 0.0, 21.21);
  ck_assert_str_eq(c, d);
  ck_assert_int_eq(
      s21_sprintf(c, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
                  21.21, 0.0, 21.21, 21., 0.0, 21.21),
      sprintf(d, "% 10f % 10f %f %.0f %.0f %#.0f %.0f %f %010f", f, f1, 21.,
              21.21, 0.0, 21.21, 21., 0.0, 21.21));
  ck_assert_int_eq(
      s21_sprintf(c, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx",
                  n, n2, 21, 0, 42, 21, 0, -65, lg, lg1),
      sprintf(d, "%#x %#x %#10x %#10x %-#10x %0#10x %0#10x %-10.5x %lx %lx", n,
              n2, 21, 0, 42, 21, 0, -65, lg, lg1));
}
END_TEST

START_TEST(sscanf_test) {
  wchar_t wc1, wc2;
  int a1 = 1, b1 = 0, i1 = 0, n1 = 0, i2 = 0, n2 = 0;
  unsigned int a2 = 1, a3 = 1, b2 = 0, b3 = 0;
  long e1 = 1, r1 = 1;
  unsigned long e2 = 0, r2 = 0;
  long double e3 = 0, e4 = 0, g3 = 0, g4 = 0, ld1 = 0, ld2 = 1;
  float f1 = 0, f2 = 1;
  char q1 = '0', w1 = '1', arr1[100] = "", arr2[100] = "";
  void *adres1 = s21_NULL, *adres2 = s21_NULL;
  ck_assert_int_eq(
      s21_sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &a1, &a2, &a3, &q1, arr1),
      sscanf(" -12345678asd", " %2d%2o%2x%1c%2s", &b1, &b2, &b3, &w1, arr2));
  ck_assert_int_eq(a1, b1);
  ck_assert_int_eq(a2, b2);
  ck_assert_int_eq(a3, b3);
  ck_assert_int_eq(q1, w1);
  ck_assert_str_eq(arr1, arr2);
  ck_assert_int_eq(s21_sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc1, &f1, &ld1),
                   sscanf("z1.25e5 1.23e+10", "%lc%G%Le", &wc2, &f2, &ld2));
  ck_assert_float_eq(f1, f2);
  ck_assert_ldouble_eq(ld1, ld2);
  ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                   sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
  ck_assert_int_eq(e1, r1);
  ck_assert_int_eq(e2, r2);
  ck_assert_int_eq(s21_sscanf("5 0x213def", "%1i%p%n", &i1, &adres1, &n1),
                   sscanf("5 0x213def", "%1i%p%n", &i2, &adres2, &n2));
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(n1, n2);
  ck_assert_ptr_eq(adres1, adres2);
  ck_assert_int_eq(
      s21_sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e3, &g3),
      sscanf("1.23451e+15 34567837433.456", "%Le%Lg", &e4, &g4));
  ck_assert_ldouble_eq(e3, e4);
  ck_assert_ldouble_eq(g3, g4);
  ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "%2li%2lo", &e1, &e2),
                   sscanf(" -123abcdeasd", "%2li%2lo", &r1, &r2));
  ck_assert_int_eq(s21_sscanf(" -123abcdeasd", "dfdf"),
                   sscanf(" -123abcdeasd", "dfdf"));
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, memchr_test);
  tcase_add_test(tc1_1, memcmp_test);
  tcase_add_test(tc1_1, memcpy_test);
  tcase_add_test(tc1_1, memmove_test);
  tcase_add_test(tc1_1, memset_test);
  tcase_add_test(tc1_1, strcat_test);
  tcase_add_test(tc1_1, strncat_test);
  tcase_add_test(tc1_1, strchr_test);
  tcase_add_test(tc1_1, strcmp_test);
  tcase_add_test(tc1_1, strncmp_test);
  tcase_add_test(tc1_1, strcpy_test);
  tcase_add_test(tc1_1, strncpy_test);
  tcase_add_test(tc1_1, strcspn_test);
  tcase_add_test(tc1_1, strerror_test);
  tcase_add_test(tc1_1, strlen_test);
  tcase_add_test(tc1_1, strpbrk_test);
  tcase_add_test(tc1_1, strrchr_test);
  tcase_add_test(tc1_1, strspn_test);
  tcase_add_test(tc1_1, strstr_test);
  tcase_add_test(tc1_1, strtok_test);
  tcase_add_test(tc1_1, to_upper_test);
  tcase_add_test(tc1_1, to_lower_test);
  tcase_add_test(tc1_1, insert_test);
  tcase_add_test(tc1_1, trim_test);
  tcase_add_test(tc1_1, sprintf_test);
  tcase_add_test(tc1_1, sscanf_test);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
