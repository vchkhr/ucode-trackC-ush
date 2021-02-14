#include "libmx.h"

void *mx_memcpy(void *restrict destination, const void *restrict src, size_t amount) {
    char *destination_p = destination;
    const char *src_p = src;

    for (; amount--;) {
        *destination_p++ = *src_p++;
    }
    
    return destination;
}

