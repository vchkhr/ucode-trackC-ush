#include "ush.h"

char *mx_substitude_commands(char *string, t_shell *shell) {
    if (!string || !*string) {
        return string;
    }

    char *res = string;

    for (int pos = 0; res && (pos = mx_index_char_quote(res, "`$", "\'")) >= 0;) {
        if (!(res = mx_combine_strings(res, pos, shell))) {
            mx_printerr("u$h: command substitushion doesn't work.\n");

            return NULL;
        }
    }
    
    return res;
}
