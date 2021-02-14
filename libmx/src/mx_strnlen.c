#include "libmx.h"

int mx_strnlen(const char *s, char c) {
	int i = 0;

	while (s[i] && s[i] != c)
		i++;

	return i;
}
