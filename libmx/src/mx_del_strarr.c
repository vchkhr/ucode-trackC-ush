#include "libmx.h"

void mx_del_strarr(char ***strings) {
    if (strings == NULL)
        return;

    char ***pointer = strings;
    char **pointers = *strings;

    for (; **pointer != NULL; (*pointer)++) {
        mx_strdel(*pointer);
    }

    free(pointers);
    *strings = NULL;
}
