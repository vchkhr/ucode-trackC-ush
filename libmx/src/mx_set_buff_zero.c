#include "libmx.h"

void mx_set_buff_zero(void *s, size_t n) {
    size_t i = 0;
    char *p = (void*)s;

    if (!s)
        return;
    while (i < n) {
        p[i] = 0;
        i++;
    }
}
