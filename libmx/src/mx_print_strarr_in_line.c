#include "libmx.h"

void mx_print_strarr_in_line(char **res, const char *delim) {
    if (!res || !delim)
        return;
    if (res[0] == NULL)
        mx_printstr("NULL\n");
    for (int i = 0; res[i]; i++) {
        mx_printstr(res[i]);
        mx_printstr(delim);
        if (res[i + 1] == NULL){
            mx_printstr("NULL\n");
        }
    }
}
