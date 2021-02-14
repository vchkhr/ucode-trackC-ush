#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    if (!src)
        return NULL;

    unsigned char buf[len];
    unsigned char *dst_cpy = dst;
    const unsigned char *src_cpy = src;

    for (size_t i = 0; i < len; i++)
        buf[i] = src_cpy[i];

    for (size_t i = 0; i < len; i++)
        dst_cpy[i] = buf[i];
    
    return dst;
}
