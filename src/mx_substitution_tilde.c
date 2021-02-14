#include "ush.h"

char *mx_substitution_tilde(char *string, t_export *export) {
    if (!string || !*string) {
        return string;
    }

    if (string[0] == '~') {
        char *result = mx_substitude_tilde(string, export);

        if (result) {
            mx_strdel(&string);

            return result;
        }
    }
    
    return string;
}
