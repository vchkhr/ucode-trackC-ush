#include "ush.h"

char *mx_string_substitution(char *string, t_export *variables, int position) {
    if (!string)
        return NULL;

    char *result = mx_strndup(string, position);
    int length = 0;
    char *subst = mx_variable_substitution(&string[position + 1], &length);

    if (subst) {
        char *value = mx_value_substitution(subst, variables);

        if (value) {
            result = mx_strjoin_free(result, value);
        }

        mx_strdel(&subst);
    }
    else {
        result = mx_strjoin_free(result, "");
    }

    if (result && string[position + length + 1]) {
        result = mx_strjoin_free(result, &string[position + length + 1]);
    }

    mx_strdel(&string);

    return result;
}

