#include "ush.h"

bool mx_check_substitution_result(char **result, char **arguments, int *n) {
    if (!result[*n]) {
        mx_del_strarr(&result);
        free(arguments);

        return true;
    }
    else if (result[*n][0] == '\0') {
        mx_strdel(&result[*n]);
        (*n)--;
    }
    
    return false;
}
