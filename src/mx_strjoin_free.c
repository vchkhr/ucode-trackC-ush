#include "libmx.h"

char *mx_strjoin_free(char *string_1, char const *string_2) {
    char *pointer = NULL;

    if (!string_1 && !string_2) {
        return NULL;
    }
    else if (!string_1) {
        pointer = mx_strdup(string_2);
    }
    else if (!string_2) {
        pointer = mx_strdup(string_1);
    }
    else {
        pointer = mx_strnew(mx_strlen(string_1) + mx_strlen(string_2));

        if (!pointer) {
            return NULL;
        }

        pointer = mx_strcpy(pointer, string_1);
        pointer = mx_strcat(pointer, string_2);
    }

    mx_strdel(&string_1);
    
    return pointer;
}
