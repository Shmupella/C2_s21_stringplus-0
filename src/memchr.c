# include "s21_string.h"

void *memchr(const void *str, int c, size_t n) {
	unsigned char *s;
	s = (unsigned char *)str;
	while (n-- != 0) {
		if (*s == (unsigned char)c) {
			return (s);
		}
		s++;
	}
	return (NULL);
}