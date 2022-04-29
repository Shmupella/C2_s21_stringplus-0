#include "s21_string.h"

char	*strchr(const char *str, int c) {
	while (*str != (unsigned char)c) {
		if (*str++ == '\0') {
			return (NULL);
        }
    }
	return ((char *)str);
}