#include "s21_string.h"

char *strcat(char *dest, const char *src) {
    char *str;
	str = dest;
	while (*dest) {
		dest++;
    }
	while ((*dest++ = *src++)) {
		;
    }
	return (str);
}
