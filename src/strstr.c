#include "s21_string.h"

char *strstr(const char *haystack, const char *needle) {
    char	*c;
	int		i;
	int		j;
	i = -1;
	c = (char *)haystack;
	if (*needle == '\0') {
        return (c);
    }
	while (c[++i] != '\0') {
		j = 0;
		while (haystack[i + j] == needle[j]) {
			if (needle[j + 1] == '\0') {
				return (&c[i]);
            }
			++j;
		}
	}
	return (NULL);
}