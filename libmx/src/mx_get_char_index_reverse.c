#include "libmx.h"

int mx_get_char_index_reverse(const char *str, char c) {
    char *s = (char *)str;
    int i;

    if (!str || !*str)
        return -2;
    i = mx_strlen(s) - 1;
    while (s[i]) {
        if (s[i] == c)
            return i;
        i--;
    }
    return -1;
}
