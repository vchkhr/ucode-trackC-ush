#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t len) {
    const unsigned char *s_cpy = s;
    unsigned char c_break = c;

    for (size_t i = 0; i < len; i++)
        if (s_cpy[i] == c_break)
            return (void *)&(s_cpy[i]);

    return NULL;
}
