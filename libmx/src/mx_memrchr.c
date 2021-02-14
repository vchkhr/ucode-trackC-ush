#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t len) {
    const unsigned char *s_cpy = s;
    unsigned char c_break = c;

    while (len > 0) {
        if (s_cpy[len] == c_break)
            return (void *)&(s_cpy[len]);

        len--;
    }

    return NULL;
}
