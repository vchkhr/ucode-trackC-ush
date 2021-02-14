#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t len) {
    for (size_t i = 0; i < len; i++) {
        ((unsigned char *)dst)[i] = ((const unsigned char *)src)[i];

        if (((const unsigned char *)src)[i] == (const unsigned char)c)
            return (void *)&(((unsigned char *)dst)[i + 1]);
    }

    return NULL;
}
