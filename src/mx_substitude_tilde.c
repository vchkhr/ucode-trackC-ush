#include "ush.h"

char *mx_substitude_tilde(char *string, t_export *export) {
    int slash;
    char *result = NULL;
    char *prefix = mx_prefix(string, &slash);

    if (prefix == NULL) {
        result = mx_tilde_result("HOME", export);
    }
    else if (prefix[0] == '/' && slash == 0) {
        result = mx_tilde_result("HOME", export);
    }
    else if (prefix[0] == '+' && !prefix[1]) {
        result = mx_tilde_result("PWD", export);
    }
    else if (mx_strcmp(prefix, "-") == 0) {
        result = mx_tilde_result("OLDPWD", export);
    }
    else {
        result = mx_user(mx_tilde_result("HOME", export), prefix);
    }

    if (result && slash >= 0) {
        result = mx_strjoin_free(result, &string[slash + 1]);
    }

    mx_strdel(&prefix);

    return result;
}
