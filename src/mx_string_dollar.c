#include "ush.h"

char *mx_string_dollar(char *string, t_export *variables) {
    if (!string || !*string || !variables || mx_strcmp(string, "$") == 0) {
        return string;
    }

    char *result = string;

    for (int i = 0, k = 0; string[i];) {
        if ((k = mx_index_char_quote(&result[i], "\"", "\'`$")) >= 0) {
            result = mx_substitude_quotes(result, variables, &i, &k);
        }
        else {
            break;
        }
    }

    for (int position = 0; result && (position = mx_index_char_quote(result, "$", "\"\'`$")) >= 0;) {
        result = mx_string_substitution(result, variables, position);
    }

    if (!result) {
        mx_printerr("ush: bad substitution\n");

        return NULL;
    }

    return result;
}
