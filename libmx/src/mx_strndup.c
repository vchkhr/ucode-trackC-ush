#include "libmx.h"

char *mx_strndup(const char *str, size_t n) {
    size_t length = mx_strlen(str);

    if (n < length)
        length = n;
    
    char *memory = mx_strnew(length);

    return mx_strncpy(memory, str, length);
}
