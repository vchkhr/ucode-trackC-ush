#include "ush.h"

char *mx_substritution(char *string, int *length) {
    char *subst = NULL;
    int iter = 0;

    if (string[0] == '$' && string[1] == '(') {
        iter = mx_index_char_quote(string, ")", "\'");

        if (iter < 0) {
            return NULL;
        }

        subst = mx_strndup(&string[2], iter - 2);
        *length = iter;
    }
    else if (string[0] == '`') {
        iter = mx_index_char_quote(&string[1], "`", "\'");

        if (iter < 0) {
            return NULL;
        }

        subst = mx_strndup(&string[1], iter);
        *length = iter + 1;
    }
    
    return subst;
}
