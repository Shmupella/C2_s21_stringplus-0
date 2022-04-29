#include "s21_string.h"

void *memcpy(void *dest, const void *src, size_t n) {
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;
	d = (unsigned char*)dst;
	s = (unsigned char*)src;
	i = -1;
	while (++i < n) {
		d[i] = s[i];
		if (s[i] == (unsigned char)c) {
			return (dst + i + 1);
        }
	}
	return (NULL);
}