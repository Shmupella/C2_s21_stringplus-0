#include "s21_string.h"

int	memcmp(const void *str1, const void *str2, size_t n) {
	const unsigned char *p1;
	const unsigned char *p2;
	p1 = str1;
	p2 = str2;
	while (n--) {
		if (*p1 != *p2) {
			return (*p1 - *p2);
        } else {
			p1++;
			p2++;
		}
	}
	return (0);
}