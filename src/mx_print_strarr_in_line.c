#include "libmx.h"

void mx_print_strarr_in_line(char **result, const char *delimiter) {
    if (!result || !delimiter) {
        return;
    }

    if (result[0] == NULL) {
        mx_printstr("NULL\n");
    }
    
    for (int i = 0; result[i]; i++) {
        mx_printstr(result[i]);
        mx_printstr(delimiter);

        if (result[i + 1] == NULL) {
            mx_printstr("NULL\n");
        }
    }
}
