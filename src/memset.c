#include "s21_string.h"

void *memset(void *str, int c, size_t n) {
    unsigned char *s;
    s = str;
	while (n-- != 0) {
		*s++ = (unsigned char)c;
    }
	return (str);
}