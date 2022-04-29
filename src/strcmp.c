#include "s21_string.h"

int	strcmp(const char *str1, const char *str2) {
	unsigned char *s1;
	unsigned char *s2;
	int	i;
	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	while (s1[i] && s1[i] == s2[i]) {
		++i;
    }
	return (s1[i] - s2[i]);
}