#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    if (big_len < 0 || little_len < 0 || big_len < little_len)
        return NULL;

    const unsigned char *full = big;
    const unsigned char *part = little;

    for (size_t i = 0; i < big_len; i++) {
        if (mx_memcmp(full, part, little_len - 1) == 0)
            return (void *)full;

        full++;
    }

    return NULL;
}
