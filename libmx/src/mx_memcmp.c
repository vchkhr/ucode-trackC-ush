#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t len) {
    if (len == 0)
        return 0;

    const unsigned char *s1_cpy = s1;
    const unsigned char *s2_cpy = s2;
    size_t i = 0;

    while (s1_cpy[i] == s2_cpy[i] && i != len) {
        if (s1_cpy[i] == '\0' && s2_cpy[i] == '\0')
            return 0;

        i++;
    }

    return s1_cpy[i] - s2_cpy[i];
}
