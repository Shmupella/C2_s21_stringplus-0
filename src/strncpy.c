#include "s21_string.h"

char *strncpy(char *dest, const char *src, size_t n) {
	size_t i;
	i = 0;
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
	return (dest);
}