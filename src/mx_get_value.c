#include "ush.h"

char *mx_get_value(char *string, int end) {
    int i = end;

    if (!string[i] || mx_strncmp(&string[i], " { ", 3) != 0) {
        return mx_error_usage();
    }

    i += 3;
    end = mx_index_char_quote(&string[i], "}", "\"\'`$(");
    
    if (end <= 0) {
        return mx_error_syntax("{");
    }

    char *value = NULL;
    
    value = mx_strndup(&string[i], end);

    return value;
}
