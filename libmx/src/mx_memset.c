#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    if (b) {
        unsigned char *b_set = b;
        unsigned char c_set = c;

        for (size_t i = 0; i < len; i++)
            b_set[i] = c_set;
    }
    
    return b;
}
