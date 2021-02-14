#include "libmx.h"

char *mx_strdup(const char *str) {
    size_t length = mx_strlen(str);
    char *memory = mx_strnew(length);

    return mx_strcpy(memory, str);
}
