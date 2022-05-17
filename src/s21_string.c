#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr;
  unsigned char chr = (unsigned char)c;
  ptr = (unsigned char *)str;
  unsigned char *check = s21_NULL;
  while (n != 0) {
    if (*ptr == chr) {
      check = ptr;
      break;
    } else {
      ptr++;
      n--;
    }
  }
  return check;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *s1;
  const unsigned char *s2;
  s1 = str1;
  s2 = str2;
  s21_size_t i = 0;
  while (i < n && s1[i]) {
    if (s1[i] == s2[i]) {
      i++;
    } else {
      break;
    }
  }
  return s1[i] - s2[i];
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  for (s21_size_t i = 0; i < n; i++) {
    *((char *)dest + i) = *((char *)src + i);
  }
  return dest;
}

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *chdest = (char *)dest;
  char *chsrc = (char *)src;
  if (chdest <= chsrc || chdest >= chsrc + n) {
    while (n--) *chdest++ = *chsrc++;
  } else {
    chdest = chdest + n - 1;
    chsrc = chsrc + n - 1;
    while (n--) *chdest-- = *chsrc--;
  }
  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s;
  s = str;
  while (n != 0) {
    *s = (unsigned char)c;
    n--;
    s++;
  }
  return str;
}

char *s21_strcat(char *dest, const char *src) {
  s21_size_t size = s21_strlen(dest);
  int i = 0;
  for (; *(src + i) != '\0'; i++) {
    *(dest + size + i) = *(src + i);
  }
  *(dest + size + i) = '\0';
  return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *s = dest;
  dest += s21_strlen(dest);
  dest[n] = '\0';
  s21_memcpy(dest, src, n);
  return s;
}

char *s21_strchr(const char *str, int c) {
  char *check = s21_NULL;
  while (*str != '\0') {
    if (*str == (unsigned char)c) {
      check = (char *)str;
      break;
    }
    str++;
  }
  return check;
}

int s21_strcmp(const char *str1, const char *str2) {
  int i = 0;
  while (str1[i] && str1[i] == str2[i]) {
    ++i;
  }
  return str1[i] - str2[i];
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t i = 0;
  int res = 0;
  while (i < n) {
    if (str1[i] == '\0') {
      res = str1[i] - str2[i];
      break;
    }
    if (str1[i] != str2[i]) {
      res = str1[i] - str2[i];
      break;
    }
    i++;
  }
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  int i = 0;
  while (src[i] != '\0') {
    dest[i] = src[i];
    i++;
  }
  dest[i] = '\0';
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i = 0;
  while (i < n) {
    if (src[i] != '\0') {
      dest[i] = src[i];
      i++;
    } else {
      while (i < n) {
        dest[i++] = '\0';
      }
    }
  }
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int count = 0;
  int i = 0;
  int flag = 0;
  while (str1[i] != '\0' && flag == 0) {
    int j = 0;
    while (str2[j] != '\0') {
      if (str1[i] != str2[j]) {
        j++;
      } else {
        flag = 1;
        break;
      }
    }
    if (flag == 0) {
      count++;
    }
    i++;
  }
  return count;
}

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

s21_size_t s21_strlen(const char *str) {
  int count = 0;
  for (int i = 0; str[i] != 0; i++) {
    count++;
  }
  return count;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *returnVal = s21_NULL;
  int i = 0;
  while (str1[i] != '\0' && returnVal == s21_NULL) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        returnVal = ((char *)str1) + i;
        break;
      }
    }
    i++;
  }
  return returnVal;
}

char *s21_strrchr(const char *str, int c) {
  int size = s21_strlen(str);
  char *res = s21_NULL;
  while (size >= 0) {
    if (str[size] == (char)c) {
      res = ((char *)str + size);
      break;
    }
    --size;
  }
  return res;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  s21_size_t flag = 0;
  while (str1[i] != '\0' && flag == 0) {
    int j;
    j = 0;
    int n;
    n = 0;
    while (str2[n] != '\0') {
      if (str1[i] == str2[n]) j++;
      n++;
    }
    if (j > 0)
      i++;
    else
      flag = 1;
  }
  return i;
}

char *s21_strstr(const char *haystack, const char *needle) {
  char *c;
  int i = -1;
  c = (char *)haystack;
  if (*needle == '\0') {
    return c;
  }
  while (c[++i] != '\0') {
    int j = 0;
    while (haystack[i + j] == needle[j]) {
      if (needle[j + 1] == '\0') {
        return (&c[i]);
      }
      ++j;
    }
  }
  return s21_NULL;
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
  str = p + s21_strspn(p, delim);
  p = str + s21_strcspn(str, delim);
  if (p == str) {
    return p = 0;
  }
  if (*p) {
    *p = 0;
    p = p + 1;
  } else {
    p = 0;
  }
  return str;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  struct format S;
  const char *start = str;
  init(&S);
  char *f = (char *)format;
  while (*f != '\0') {
    if (*f == '%') {
      f++;
      while (*f == '-' || *f == '+' || *f == ' ' || *f == '#' || *f == '0') {
        if (*f == '-')
          S.flag_minus = 1;
        else if (*f == '+')
          S.flag_plus = 1;
        else if (*f == ' ')
          S.flag_space = 1;
        else if (*f == '#')
          S.flag_hash = 1;
        else if (*f == '0')
          S.flag_zero = 1;
        f++;
      }
      while ((*f >= '0' && *f <= '9') || *f == '*') {
        if (*f >= '0' && *f <= '9')
          S.wight = S.wight * 10 + (*f - '0');
        else if (*f == '*')
          S.wight = va_arg(ap, int);
        f++;
      }
      if (*f == '.') {
        S.accur = 0;
        f++;
        while ((*f >= '0' && *f <= '9') || *f == '*') {
          if (*f >= '0' && *f <= '9')
            S.accur = S.accur * 10 + (*f - '0');
          else if (*f == '*')
            S.accur = va_arg(ap, int);
          f++;
        }
      }
      if (*f == 'h' || *f == 'l' || *f == 'L') S.lenght = *f++;
      if (*f == 'c' || *f == 'd' || *f == 'i' || *f == 'e' || *f == 'E' ||
          *f == 'f' || *f == 'g' || *f == 'G' || *f == 'o' || *f == 's' ||
          *f == 'u' || *f == 'x' || *f == 'X' || *f == 'p' || *f == 'n')
        S.spec = *f++;
      else if (*f == '%')
        *str++ = *f++;
      if (S.spec == 'c') {
        badflags(&S);
        if (S.lenght == 'l')
          str = c_sprintf(&S, str, (int)va_arg(ap, wchar_t));
        else
          str = c_sprintf(&S, str, va_arg(ap, int));
      } else if (S.spec == 'd' || S.spec == 'i') {
        badflags(&S);
        if (S.lenght == 'l')
          str = ld_sprintf(&S, str, va_arg(ap, long int));
        else
          str = d_sprintf(&S, str, va_arg(ap, int));
      } else if (S.spec == 's') {
        badflags(&S);
        if (S.lenght == 'l') {
          wchar_t *y = va_arg(ap, wchar_t *);
          str = ls_sprintf(&S, str, y);
        } else {
          char *x = va_arg(ap, char *);
          str = s_sprintf(&S, str, x);
        }
      } else if (S.spec == 'n') {
        n_sprintf(str, start, va_arg(ap, int *));
      } else if (S.spec == 'o' || S.spec == 'x' || S.spec == 'X') {
        badflags(&S);
        if (S.lenght == 'l')
          str = loxX_sprintf(&S, str, va_arg(ap, long int));
        else
          str = oxX_sprintf(&S, str, va_arg(ap, int));
      } else if (S.spec == 'u') {
        badflags(&S);
        if (S.lenght == 'l')
          str = lu_sprintf(&S, str, va_arg(ap, s21_size_t_long));
        else
          str = u_sprintf(&S, str, va_arg(ap, s21_size_t));
      } else if (S.spec == 'f') {
        str = f_sprintf(&S, str, va_arg(ap, double));
      } else if (S.spec == 'p') {
        badflags(&S);
        str = p_sprintf(str, va_arg(ap, void *));
      }
      init(&S);
    } else {
      *str++ = *f++;
    }
  }
  int result = str - start;
  va_end(ap);
  return result;
}

int s21_sscanf(const char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  struct fsc S;
  char *f = (char *)format;
  S.str = S.start = (char *)str;
  S.result = *S.str == '\0' ? -1 : 0;
  S.error = 0;
  while (*f != '\0') {
    init_scanf(&S);
    if (*f == '%' && *(f + 1) != '\0') {
      f++;
      if (*f == '*') {
        S.ast = 1;
        f++;
      }
      while (*f >= '0' && *f <= '9') S.wight = S.wight * 10 + (*f++ - '0');
      if (*f == 'h' || *f == 'l' || *f == 'L') S.lenght = *f++;
      if ((S.error && *f != 'n') || !spec_scanf(*f, &S, ap)) break;
      is_error(&S);
    }
    f++;
  }
  va_end(ap);
  return S.result;
}

void *s21_to_upper(const char *str) {
  char *str_up = s21_NULL;
  if (str != s21_NULL) {
    int size = s21_strlen(str) + 1;
    str_up = malloc(size * sizeof(char));
    int i;
    for (i = 0; str[i]; i++) {
      if (str[i] >= 97 && str[i] <= 122) {
        str_up[i] = str[i] - 32;
      } else {
        str_up[i] = str[i];
      }
    }
    str_up[i] = '\0';
  }
  return str_up;
}

void *s21_to_lower(const char *str) {
  char *str_low = s21_NULL;
  if (str != s21_NULL) {
    int size = s21_strlen(str) + 1;
    int i;
    str_low = malloc(size * sizeof(char));
    for (i = 0; str[i]; i++) {
      if (str[i] <= 90 && str[i] >= 65) {
        str_low[i] = str[i] + 32;
      } else {
        str_low[i] = str[i];
      }
    }
    str_low[i] = '\0';
  }
  return str_low;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *new_str = NULL;
  if (src && str && s21_strlen(src) >= start_index) {
    new_str =
        (char *)malloc((s21_strlen(src) + s21_strlen(str) + 1) * sizeof(char));
    if (new_str) {
      s21_strncpy(new_str, src, start_index);
      *(new_str + start_index) = '\0';
      s21_strcat(new_str, str);
      s21_strcat(new_str, src + start_index);
    }
  }
  return (void *)new_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  char *src_new = s21_NULL;
  if (src != s21_NULL && trim_chars != s21_NULL) {
    int size = s21_strlen(src) + 1;
    src_new = malloc(size * sizeof(char));
    int i = 0, k = size - 2, flag = 1, l;
    while (src[i] && flag) {
      flag = 0;
      for (int j = 0; trim_chars[j]; j++) {
        if (src[i] == trim_chars[j]) {
          flag = 1;
          i++;
          break;
        }
      }
    }
    flag = 1;
    while (k >= 0 && flag) {
      flag = 0;
      for (int j = 0; trim_chars[j]; j++) {
        if (src[k] == trim_chars[j]) {
          flag = 1;
          k--;
          break;
        }
      }
    }
    k = k - i;
    for (l = 0; l <= k; i++, l++) src_new[l] = src[i];
    src_new[l] = '\0';
  }
  return src_new;
}

void convert(unsigned int num, int x, struct format *S, char *str) {
  const char arr[] = "0123456789abcdef";
  const char arr1[] = "0123456789ABCDEF";
  int i = 0;
  char buf[1024] = {};
  if (S->spec == 'x' || S->spec == 'o') {
    while (num != 0 && x != 0) {
      buf[i++] = arr[num % x];
      num /= x;
    }
  }
  if (S->spec == 'X') {
    while (num != 0 && x != 0) {
      buf[i++] = arr1[num % x];
      num /= x;
    }
  }
  buf[i] = '\0';
  reverse(buf);
  s21_strcat(str, buf);
}

void convert_f_long(unsigned long int num, int x, struct format *S, char *str) {
  const char arr[] = "0123456789abcdef";
  const char arr1[] = "0123456789ABCDEF";
  int i = 0;
  char buf[1024] = {};
  if (S->spec == 'x' || S->spec == 'o') {
    while (num != 0 && x != 0) {
      buf[i++] = arr[num % x];
      num /= x;
    }
  }
  if (S->spec == 'X') {
    while (num != 0 && x != 0) {
      buf[i++] = arr1[num % x];
      num /= x;
    }
  }
  buf[i] = '\0';
  reverse(buf);
  s21_strcat(str, buf);
}

void utoa(s21_size_t n, char *str) {
  int i = 0;
  if (n == 0) {
    str[i] = n + '0';
    i++;
  } else {
    while (n > 0) {
      str[i] = n % 10 + '0';
      i++;
      n /= 10;
    }
  }
  str[i] = '\0';
  reverse(str);
}

void lutoa(s21_size_t_long n, char *str) {
  int i = 0;
  while (n > 0) {
    str[i] = n % 10 + '0';
    i++;
    n /= 10;
  }
  str[i] = '\0';
  reverse(str);
}

void ltoa(long int n, char *str, struct format *S) {
  int i = 0;
  if (n < 0) {
    n = n * -1;
  }
  while (n > 0) {
    str[i++] = n % 10 + '0';
    n /= 10;
  }
  if (S->negative == 1) {
    str[i++] = '-';
  }
  str[i] = '\0';
  reverse(str);
}

void flagHash(char *c, struct format *S, int i) {
  c[i++] = '0';
  if (S->spec == 'x')
    c[i++] = 'x';
  else if (S->spec == 'X')
    c[i++] = 'X';
}

void flagMinus(char *c, struct format *S) {
  char temp[1024] = {};
  int i = 0;
  if (S->accur > -1) {
    if (S->flag_plus && c[0] != '-' && !S->minus) temp[i++] = '+';
    S->flag_plus = 0;
  }
  if (S->flag_hash && !S->flag_zero &&
      (S->spec == 'o' || S->spec == 'x' || S->spec == 'X')) {
    int x = i;
    flagHash(temp, S, x);
  }
  if (S->minus) {
    temp[i++] = '-';
    s21_strcat(temp, c);
  } else if (S->flag_plus) {
    S->flag_space = 0;
    temp[i++] = '+';
    s21_strcat(temp, c);
  } else if (S->flag_space) {
    temp[i++] = ' ';
    s21_strcat(temp, c);
  } else {
    s21_strcat(temp, c);
  }
  int len = s21_strlen(temp);
  if (S->wight < len) S->wight = len;
  while (len < S->wight) temp[len++] = ' ';
  temp[len] = '\0';
  s21_strcpy(c, temp);
}

void flagPlusSpase(char *c, struct format *S) {
  char buf[1024] = {};
  int i = 0;
  if (S->flag_hash && (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
    flagHash(buf, S, i);
  i = 0;
  if (S->flag_plus) {
    S->flag_space = 0;
    buf[i++] = '+';
  }
  if (S->flag_space) buf[i++] = ' ';
  s21_strcat(buf, c);
  i = 0;
  while (buf[i]) *c++ = buf[i++];
  *c = '\0';
}

void accur_s(char *c, struct format *S) {
  char buf[1024] = {};
  int len = s21_strlen(c);
  int i = 0;
  if (S->accur < len) {
    len = S->accur;
  }
  while (len > 0) {
    buf[i++] = *c++;
    len--;
  }
  s21_strcpy(c, buf);
  *c = '\0';
}

void accur_d(char *str, struct format *S) {
  S->accur_spec_d = 1;
  S->flag_zero = 0;
  char temp_in[1024] = {};
  char *c = temp_in;
  s21_strcpy(c, str);
  int len = s21_strlen(temp_in);
  int min = 0;
  char temp[1024] = {};
  char *b = temp;
  if (c[0] == '-') {
    min = 1;
    c[0] = '0';
  }
  if (S->accur > len) {
    int i = 0;
    if (S->flag_hash && S->spec == 'o') len++;
    if (min && S->accur >= len + 1) {
      b[i++] = '-';
    }
    while (len != S->accur) {
      b[i++] = '0';
      len++;
    }
    b[i] = '\0';
    s21_strcat(b, c);
    s21_strcpy(str, b);
  }
}

void wight(char *c, struct format *S) {
  char buf[1024] = {};
  int len = s21_strlen(c);
  int i = 0;
  int W = S->wight;
  if ((S->minus || S->flag_plus) && S->wight <= len) {
    if (S->minus)
      buf[i++] = '-';
    else if (S->flag_plus)
      buf[i++] = '+';
  }
  if (S->flag_space && !S->minus && !S->flag_plus) {
    buf[i++] = ' ';
    W--;
  }
  if (S->minus && S->flag_zero) {
    buf[i++] = '-';
    W--;
  }
  if (S->flag_plus && !S->minus && S->flag_zero) {
    buf[i++] = '+';
    W--;
  }
  while (W-- > len) {
    if (S->flag_zero && S->spec != 'c' && S->spec != 's' && S->spec != 'n' &&
        S->spec != 'p')
      buf[i++] = '0';
    else
      buf[i++] = ' ';
  }
  if (S->minus && !S->flag_zero) buf[i - 1] = '-';
  if (S->flag_plus && !S->minus && !S->flag_zero) {
    if (S->accur > -1 && c[0] != '-')
      buf[i - 1] = '+';
    else
      buf[i - 1] = '+';
  }
  s21_strcat(buf, c);
  i = 0;
  while (buf[i]) *c++ = buf[i++];
  *c = '\0';
}

void wight_oxX(char *c, struct format *S) {
  char buf[1024] = {};
  int len = s21_strlen(c);
  int i = 0;
  int W = S->wight;
  if (S->flag_hash) {
    if (S->spec == 'o') W--;
    if (S->spec == 'x' || (S->spec == 'X')) W -= 2;
  }
  if (!S->flag_zero) {
    while (W-- > len) buf[i++] = ' ';
  }
  if (S->flag_hash) {
    flagHash(buf, S, i);
    if (S->spec == 'o')
      i += 1;
    else if (S->spec == 'x' || S->spec == 'X')
      i += 2;
  }
  if (S->flag_zero) {
    while (W-- > len) buf[i++] = '0';
  }
  s21_strcat(buf, c);
  i = 0;
  while (buf[i]) *c++ = buf[i++];
}

void lenght(int x, char *str, struct format *S) {
  if (S->lenght == 'h') x = (short)x;
  itoa((int)x, str);
}

void format(struct format *S, char *str) {
  if (S->spec == 's') {
    if (S->accur > 0) accur_s(str, S);
    if (S->accur == 0) *str = '\0';
  } else if (S->accur > 0) {
    accur_d(str, S);
  }
  if (S->wight > 0 && !S->flag_minus &&
      (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
    wight_oxX(str, S);
  else if (S->wight > 0 && !S->flag_minus)
    wight(str, S);
  else if (S->flag_minus && S->wight > 0)
    flagMinus(str, S);
  if (!S->wight && S->negative == 0 && (S->flag_plus || S->flag_space))
    flagPlusSpase(str, S);
  if (!S->wight && S->flag_hash &&
      (S->spec == 'o' || S->spec == 'x' || S->spec == 'X'))
    flagPlusSpase(str, S);
}

void formatF(struct format *S, char *str, int num) {
  if (S->wight > 0 && !S->flag_minus)
    wight(str, S);
  else if (S->flag_minus && S->wight > 0)
    flagMinus(str, S);
  if (!S->wight && num >= 0 && (S->flag_plus || S->flag_space))
    flagPlusSpase(str, S);
}

char *d_sprintf(struct format *S, char *str, int num) {
  char arr[1024];
  char *c = arr;
  if (num < 0 && S->wight && S->accur == -1) {
    S->minus = 1;
    num *= -1;
  }
  if (S->lenght == 'h')
    lenght(num, arr, S);
  else
    itoa(num, arr);
  if (S->accur == 0 && num == 0) *c = '\0';
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *ld_sprintf(struct format *S, char *str, long int num) {
  char arr[1024];
  char *c = arr;
  if (num == LLONG_MIN) {
    c = "-9223372036854775808";
  } else {
    if (num < 0) S->negative = 1;
    ltoa(num, arr, S);
  }
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *oxX_sprintf(struct format *S, char *str, int num) {
  char arr[1024] = {};
  char *c = arr;
  if (num == 0) {
    int i = 0;
    arr[i++] = num + '0';
    S->flag_hash = 0;
  } else if (S->spec == 'o') {
    convert(num, 8, S, c);
    if (num < 0 && S->lenght == 'h') {
      c += 5;
      *c = '1';
    }
  } else if (S->spec == 'x' || S->spec == 'X') {
    convert(num, 16, S, c);
    if (num < 0 && S->lenght == 'h') c += 4;
  }
  if (S->accur == 0 && num == 0) *c = '\0';
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *loxX_sprintf(struct format *S, char *str, long int num) {
  char arr[1024] = {};
  char *c = arr;
  if (S->spec == 'o' && num != 0) {
    convert_f_long(num, 8, S, c);
  } else if ((S->spec == 'x' || S->spec == 'X') && num != 0) {
    convert_f_long(num, 16, S, c);
  }
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *c_sprintf(struct format *S, char *str, int C) {
  char arr[1024] = {};
  char *c = arr;
  *c = (char)C;
  if (S->wight > 0 && !S->flag_minus)
    wight(c, S);
  else if (S->flag_minus && S->wight > 0)
    flagMinus(c, S);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *s_sprintf(struct format *S, char *str, char *C) {
  char arr[1024] = {};
  int i = 0;
  while (*C) arr[i++] = *C++;
  char *c = arr;
  format(S, c);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *ls_sprintf(struct format *S, char *str, wchar_t *C) {
  char arr[1024] = {};
  char temp[1024] = {};
  char *c = temp;
  int i = 0;
  while (C[i] != '\0') {
    arr[i] = (char)C[i];
    i++;
  }
  int len = s21_strlen(arr);
  i = 0;
  while (len) {
    c[i] = arr[i];
    i++;
    len--;
  }
  format(S, c);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *u_sprintf(struct format *S, char *str, s21_size_t num) {
  if (S->accur > S->wight) {
    S->wight = S->accur;
    S->flag_zero = 1;
  }
  char arr[1024];
  char *c = arr;
  utoa(num, arr);
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *lu_sprintf(struct format *S, char *str, s21_size_t_long num) {
  if (S->accur > S->wight) {
    S->wight = S->accur;
    S->flag_zero = 1;
  }
  char arr[1024];
  char *c = arr;
  lutoa(num, arr);
  format(S, arr);
  while (*c) *str++ = *c++;
  *str = '\0';
  return str;
}

char *p_convert(long x, int hex) {
  long num = x;
  const char arr[] = "0123456789abcdef";
  static char buffer[1024];
  char *ptr = buffer;
  while (num != 0 && hex != 0) {
    *--ptr = arr[num % hex];
    num /= hex;
  }
  return (ptr);
}

void *p_sprintf(char *str, void *ptr) {
  static char string_pointer[1024] = "0x";
  char *p = string_pointer;
  long x = (long)ptr;
  char *buf = p_convert(x, 16);
  s21_strcat(string_pointer, buf);
  while (*p) *str++ = *p++;
  *str = '\0';
  return str;
}

void n_sprintf(const char *str, const char *start, int *path) {
  *path = str - start;
}

void init(struct format *S) {
  S->flag_plus = 0;
  S->flag_minus = 0;
  S->flag_space = 0;
  S->flag_hash = 0;
  S->flag_zero = 0;
  S->wight = 0;
  S->accur = -1;
  S->accur_spec_d = 0;
  S->minus = 0;
  S->lenght = '0';
  S->spec = '0';
  S->negative = 0;
}

void badflags(struct format *S) {
  if (S->spec == 'c') {
    S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
    S->accur = -1;
    if (S->lenght == 'h' || S->lenght == 'L') S->lenght = '0';
  } else if (S->spec == 'd' || S->spec == 'i') {
    S->flag_hash = 0;
    if (S->lenght == 'L') S->lenght = '0';
    if (S->flag_minus && S->flag_zero) S->flag_minus = S->flag_zero = 0;
    if (S->flag_space && S->flag_plus) S->flag_space = 0;
  } else if (S->spec == 's') {
    S->flag_plus = S->flag_space = S->flag_hash = S->flag_zero = 0;
    if (S->lenght == 'h' || S->lenght == 'L') S->lenght = '0';
  } else if (S->spec == 'o' || S->spec == 'x' || S->spec == 'X') {
    S->flag_plus = S->flag_space = 0;
    if (S->flag_minus && S->flag_zero) S->flag_minus = S->flag_zero = 0;
    if (S->lenght == 'L') S->lenght = '0';
  } else if (S->spec == 'u') {
    S->flag_plus = S->flag_hash = S->flag_space = 0;
    if (S->lenght == 'L') S->lenght = '0';
  } else if (S->spec == 'p') {
    S->flag_plus = S->flag_hash = S->flag_space = S->flag_zero = 0;
  }
}

char *f_sprintf(struct format *S, char *str, long double num) {
  if (S->accur == -1) S->accur = 6;
  if (num < 0 && S->wight) {
    S->minus = 1;
    num *= -1;
  }
  char arr[1024] = {};
  char *c = arr;
  int celoe = 0;
  celoe = !S->accur ? (int)round(num) : (int)num;
  itoa(celoe, c);
  if (S->flag_hash || S->accur) s21_strcat(c, ".");
  if (S->accur) {
    long double ostatok = num - (int)num;
    int acc = S->accur;
    while (acc--) ostatok *= 10;
    char fl[1024] = {};
    char *f = fl;
    itoa(abs((int)round(ostatok)), f);
    int len = s21_strlen(f);
    while (len++ < S->accur) s21_strcat(c, "0");
    s21_strcat(c, f);
  }
  formatF(S, c, num);
  while (*c) *str++ = *c++;
  *str = '\0';
  s21_strcat(str, c);
  return str;
}

void itoa(int n, char *str) {
  int i = 0;
  long int x = n;
  if (n < 0) x *= -1;
  if (!x) str[i++] = '0';
  while (x > 0) {
    str[i] = x % 10 + '0';
    i++;
    x /= 10;
  }
  if (n < 0) {
    str[i] = '-';
    i++;
  }
  str[i] = '\0';
  reverse(str);
}

void reverse(char *str) {
  int k, j;
  for (k = 0, j = s21_strlen(str) - 1; k < j; k++, j--) {
    char buf = str[k];
    str[k] = str[j];
    str[j] = buf;
  }
}

void init_scanf(struct fsc *S) {
  S->wight = 0;
  S->lenght = '0';
  S->minus = 1;
  S->ast = 0;
  S->wight = 0;
}

void *temp_adress(void) {
  static int temp[1000] = {0};
  void *adress = temp;
  return adress;
}

int is_error(struct fsc *S) {
  if (!*S->str) S->error = 1;
  return S->error;
}

void spaces_sign(struct fsc *S) {
  while (!s_valid(S->str)) S->str++;
  if (*S->str == '-') {
    S->minus = -1;
    S->str++;
    S->wight--;
  } else if (*S->str == '+') {
    S->str++;
    S->wight--;
  }
}

void c_sscanf(struct fsc *S, va_list ap) {
  char *path = temp_adress();
  if (!S->ast) path = va_arg(ap, char *);
  if (*S->str) {
    *path = *S->str++;
    if (!S->ast) S->result++;
  }
}

void lc_sscanf(struct fsc *S, va_list ap) {
  wchar_t *path = temp_adress();
  if (!S->ast) path = va_arg(ap, wchar_t *);
  if (*S->str) {
    *path = (wchar_t)*S->str++;
    S->result++;
  }
}

int s_valid(char *c) {
  int res = 1;
  switch (*c) {
    case '\n':
    case '\t':
    case '\v':
    case '\f':
    case '\r':
    case ' ':
      res = 0;
      break;
  }
  return res;
}

void s_sscanf(struct fsc *S, va_list ap) {
  char *path = temp_adress();
  if (!S->ast) path = va_arg(ap, char *);
  while (!s_valid(S->str)) S->str++;
  int res = 0;
  while (!is_error(S) && s_valid(S->str) && S->wight--) {
    *path++ = *S->str++;
    res = 1;
  }
  if (res && !S->ast) S->result += res;
  *path = '\0';
}

void ls_sscanf(struct fsc *S, va_list ap) {
  wchar_t *path = (wchar_t *)temp_adress();
  if (!S->ast) path = va_arg(ap, wchar_t *);
  while (!s_valid(S->str)) S->str++;
  int res = 0;
  while (!is_error(S) && s_valid(S->str) && S->wight--) {
    *path++ = *S->str++;
    res = 1;
  }
  if (res && !S->ast) S->result += res;
  *path = '\0';
}

void d_isresult(int res, struct fsc *S, int *path) {
  if (res && !S->ast) {
    S->result++;
    *path *= S->minus;
  }
}

void ld_isresult(int res, struct fsc *S, long *path) {
  if (res && !S->ast) {
    S->result++;
    *path *= S->minus;
  }
}

int d_valid(char c) {
  int res = 0;
  if (c >= '0' && c <= '9') res = 1;
  return res;
}

int o_convert(int value) {
  if (value >= '0' && value <= '7') value -= '0';
  if (value >= '8' && value <= '9') value = 0;
  return value;
}

int x_convert(int value) {
  if (value >= '0' && value <= '9')
    value -= '0';
  else if (value == 'x')
    value = 0;
  else if (value == 'a' || value == 'A')
    value = 10;
  else if (value == 'b' || value == 'B')
    value = 11;
  else if (value == 'c' || value == 'C')
    value = 12;
  else if (value == 'd' || value == 'D')
    value = 13;
  else if (value == 'e' || value == 'E')
    value = 14;
  else if (value == 'f' || value == 'F')
    value = 15;
  return value;
}
int o_valid(int value) {
  int res = 0;
  if (value >= '0' && value <= '7') res = 1;
  return res;
}
void strtoi(int *res, struct fsc *S, int n, int *path) {
  if (*res == 0) {
    *path = 0;
    *res = 1;
  }
  if (*S->str == 'x')
    if (!S->wight || !d_valid(*(S->str + 1))) S->error = 1;
  if (n == 10)
    *path = *path * n + (*S->str - '0');
  else if (n == 8)
    *path = *path * n + o_convert(*S->str);
  else if (n == 16)
    *path = *path * n + x_convert(*S->str);
  S->str++;
}

void strtoli(int *res, struct fsc *S, int n, long *path) {
  if (*res == 0) {
    *path = 0;
    *res = 1;
  }
  if (*S->str == 'x')
    if (S->wight == 0 || !d_valid(*(S->str + 1))) S->error = 1;
  if (n == 10)
    *path = *path * n + (*S->str - '0');
  else if (n == 8)
    *path = *path * n + o_convert(*S->str);
  else if (n == 16)
    *path = *path * n + x_convert(*S->str);
  S->str++;
}

void d_sscanf(struct fsc *S, va_list ap) {
  int temp[1000];
  int *path = temp;
  if (!S->ast) path = va_arg(ap, int *);
  spaces_sign(S);
  int res = 0;
  while (d_valid(*S->str) && S->wight--) strtoi(&res, S, 10, path);
  d_isresult(res, S, path);
  if (S->lenght == 'h') *path = (unsigned short)*path;
}

void ld_sscanf(struct fsc *S, va_list ap) {
  long *path = temp_adress();
  if (!S->ast) path = va_arg(ap, long *);
  spaces_sign(S);
  int res = 0;
  while (d_valid(*S->str) && S->wight--) strtoli(&res, S, 10, path);
  ld_isresult(res, S, path);
}

void o_sscanf(struct fsc *S, va_list ap) {
  int *path = temp_adress();
  if (!S->ast) path = va_arg(ap, int *);
  spaces_sign(S);
  int res = 0;
  while (o_valid(*S->str) && S->wight--) strtoi(&res, S, 8, path);
  d_isresult(res, S, path);
  if (S->lenght == 'h') *path = (unsigned short)*path;
}

void lo_sscanf(struct fsc *S, va_list ap) {
  long *path = temp_adress();
  if (!S->ast) path = va_arg(ap, long *);
  spaces_sign(S);
  int res = 0;
  while (o_valid(*S->str) && S->wight--) strtoli(&res, S, 8, path);
  ld_isresult(res, S, path);
}

int x_valid(int value) {
  int result = 0;
  if ((value >= '0' && value <= '9') || (value == 'x' || value == 'X') ||
      (value >= 'a' && value <= 'f') || (value >= 'A' && value <= 'F'))
    result = 1;
  return result;
}

void x_sscanf(struct fsc *S, va_list ap) {
  int *path = temp_adress();
  if (!S->ast) path = va_arg(ap, int *);
  spaces_sign(S);
  int res = 0;
  while (x_valid(*S->str) && S->wight--) {
    if (*S->str == 'x' && !d_valid(*(S->str + 1))) S->error = 1;
    strtoi(&res, S, 16, path);
  }
  d_isresult(res, S, path);
  if (S->lenght == 'h') *path = (unsigned short)*path;
}

void lx_sscanf(struct fsc *S, va_list ap) {
  long *path = temp_adress();
  if (!S->ast) path = va_arg(ap, long *);
  spaces_sign(S);
  int res = 0;
  while (x_valid(*S->str) && S->wight--) strtoli(&res, S, 16, path);
  ld_isresult(res, S, path);
}

void i_sscanf(struct fsc *S, va_list ap) {
  spaces_sign(S);
  if (*S->str == '0' && *(S->str + 1) == 'x')
    x_sscanf(S, ap);
  else if (*S->str == '0')
    o_sscanf(S, ap);
  else if (d_valid(*S->str))
    d_sscanf(S, ap);
}

void li_sscanf(struct fsc *S, va_list ap) {
  spaces_sign(S);
  if (*S->str == '0' && *(S->str + 1) == 'x')
    lx_sscanf(S, ap);
  else if (*S->str == '0')
    lo_sscanf(S, ap);
  else if (d_valid(*S->str))
    ld_sscanf(S, ap);
}

void n_sscanf(struct fsc *S, va_list ap) {
  int *path = temp_adress();
  if (!S->ast) path = va_arg(ap, int *);
  *path = S->str - S->start;
}

long double strtolda(struct fsc *S, int *res) {
  spaces_sign(S);
  long double path = 0;
  while (d_valid(*S->str) && S->wight--) {
    path = path * 10 + (*S->str - '0');
    S->str++;
    *res = 1;
  }
  if (*S->str >= '.' && S->wight) {
    S->str++;
    S->wight--;
    long double x = 10;
    while (d_valid(*S->str) && S->wight--) {
      path = path + (*S->str - '0') / x;
      x *= 10;
      S->str++;
    }
  }
  if ((*S->str == 'e' || *S->str == 'E') && S->wight) {
    S->str++;
    S->wight--;
    int minus = 0;
    long double exp = 10;
    if (*S->str == '+' && S->wight) {
      S->str++;
      S->wight--;
    } else if (*S->str == '-' && S->wight) {
      S->str++;
      S->wight--;
      minus = 1;
    }
    int num = 0;
    while (d_valid(*S->str) && S->wight--) num = num * 10 + *S->str++ - '0';
    exp = powl(10, num);
    path = minus ? path / exp : path * exp;
  }
  if (*res && !S->ast) S->result++;
  path *= S->minus;
  return path;
}

void f_sscanf(struct fsc *S, va_list ap) {
  float *path = temp_adress();
  if (!S->ast) path = va_arg(ap, float *);
  int res = 0;
  float result = (float)strtolda(S, &res);
  if (res) *path = result;
}

void lf_sscanf(struct fsc *S, va_list ap) {
  double *path = temp_adress();
  if (!S->ast) path = va_arg(ap, double *);
  int res = 0;
  double result = (double)strtolda(S, &res);
  if (res) *path = result;
}

int f_valid(char c) {
  int res = 0;
  if (c >= '0' && c <= '9')
    res = 1;
  else if (c == '.' || c == '-' || c == 'e' || c == '+')
    res = 1;
  return res;
}

void llf_sscanf(struct fsc *S, va_list ap) {
  while (*S->str == ' ') S->str++;
  long double *path = temp_adress();
  if (!S->ast) path = va_arg(ap, long double *);
  char *a = temp_adress();
  int i = 0;
  while (S->wight-- && f_valid(*S->str)) *(a + i++) = *S->str++;
  *(a + i) = '\0';
  long double result = strtold(a, &a);
  if (i && !S->ast) {
    *path = result;
    S->result++;
  }
}

void p_sscanf(struct fsc *S, va_list ap) {
  void **path = (void *)temp_adress();
  spaces_sign(S);
  if (!S->ast) path = va_arg(ap, void **);
  long adres = 0;
  int res = 0;
  while (x_valid(*S->str) && S->wight--) {
    adres = adres * 16 + x_convert(*S->str);
    S->str++;
    res = 1;
  }
  if (res && !S->ast) S->result++;
  *path = (void *)adres;
}

void l_spec_scanf(struct fsc *S, va_list ap) {
  if (S->spec == 'c')
    lc_sscanf(S, ap);
  else if (S->spec == 'i')
    li_sscanf(S, ap);
  else if (S->spec == 'o')
    lo_sscanf(S, ap);
  else if (S->spec == 's')
    ls_sscanf(S, ap);
  else if (S->spec == 'x' || S->spec == 'X')
    lx_sscanf(S, ap);
  else if (S->spec == 'd' || S->spec == 'u')
    ld_sscanf(S, ap);
  else if (S->spec == 'f' || S->spec == 'G' || S->spec == 'g' ||
           S->spec == 'E' || S->spec == 'e')
    lf_sscanf(S, ap);
}

int spec_scanf(char spec, struct fsc *S, va_list ap) {
  int result = 1;
  S->spec = spec;
  if (S->wight == 0) S->wight = 999999;
  if (S->lenght == 'l')
    l_spec_scanf(S, ap);
  else if (spec == 'c')
    c_sscanf(S, ap);
  else if (spec == 'i')
    i_sscanf(S, ap);
  else if (spec == 'o')
    o_sscanf(S, ap);
  else if (spec == 's')
    s_sscanf(S, ap);
  else if (spec == 'p')
    p_sscanf(S, ap);
  else if (spec == 'n')
    n_sscanf(S, ap);
  else if (spec == 'x' || spec == 'X')
    x_sscanf(S, ap);
  else if (spec == 'd' || spec == 'u')
    d_sscanf(S, ap);
  else if ((spec == 'f' || spec == 'G' || spec == 'g' || spec == 'E' ||
            spec == 'e') &&
           S->lenght == 'L')
    llf_sscanf(S, ap);
  else if (spec == 'f' || spec == 'G' || spec == 'g' || spec == 'E' ||
           spec == 'e')
    f_sscanf(S, ap);
  else
    result = 0;
  return result;
}
