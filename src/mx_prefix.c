#include "ush.h"

char *mx_prefix(char *string, int *position) {
    char *prefix = NULL;
    int slash = -1;

    if (string[1]) {
        slash = mx_index_char_quote(&string[1], "/", "\"\'`$(");

        if (slash > 0) {
            prefix = mx_strndup(&string[1], slash);
        }
        else {
            prefix = mx_strdup(&string[1]);
        }
    }

    *position = slash;
    
    return prefix;
}
