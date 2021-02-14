#include "libmx.h"

char *mx_strcpy(char *dst, const char *src) {
    char *str = dst;

    while (*src) {
        *dst = *src;

        dst++;
        src++;
    }

    *dst = '\0';

    return str;
}
