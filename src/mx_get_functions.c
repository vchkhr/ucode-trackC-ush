#include "ush.h"

bool mx_get_functions(char *string, t_shell *shell) {
    char *temp;
    char *value;
    int n = mx_index_char_quote(string, "(", "\"\'`$");

    if (string[n + 1] && string[n + 1] == ')') {
        if (!(temp = mx_get_var(string, n))) {
            return true;
        }

        if (!(value = mx_get_value(string, n + 2))) {
            mx_strdel(&temp);

            return true;
        }

        if (shell->functions) {
            mx_set_variable(shell->functions, temp, value);
        }
        else {
            mx_export_push(&shell->functions, temp, value);
        }

        mx_strdel(&temp);
        mx_strdel(&value);

        return true;
    }

    return false;
}
