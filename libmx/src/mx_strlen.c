#include "libmx.h"

int mx_strlen(const char *s) {
    if (!s)
        return 0;

    int len = 0;

    while (s[len])
        len++;

    return len;
}
