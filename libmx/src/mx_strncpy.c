#include "libmx.h"

char *mx_strncpy(char *dst, const char *src, int n) {
    int i = 0;

    while (src[i] && i != n) {
        dst[i] = src[i];
        i++;
    }
    
    return dst;
}
