#include "libmx.h"

void mx_set_buff_zero(void *string, size_t amount) {
    if (!string)
        return;
    
    char *p = (void*)string;

    for (size_t i = 0; i < amount; i++) {
        p[i] = 0;
    }
}
