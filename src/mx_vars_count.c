#include "ush.h"

int mx_vars_count(char **arguments, int options) {
    int variables = 0;

    for (int i = options + 1; arguments[i] != NULL; i++, variables++) {
        if (mx_get_char_index(arguments[i],'=') < 0) {
            break;
        }

        if (mx_get_char_index(arguments[i],'=') == 0) {
            mx_printerr("env: setenv ");
            mx_printerr(arguments[i]);
            mx_printerr(": Invalid argument\n");

            return -1;
        }
    }
    
    return variables;
}
