#include "ush.h"

t_ast *mx_all_commands(t_ast *result, char *string, t_shell *shell, int amount) {
    if (mx_check_errors_parsing(string)) {
        return NULL;
    }

    int type = 0;
    char *temp = NULL;
    char *line;

    line = mx_strdup(string);

    for (int i = 0; line[i];) {
        if ((temp = mx_get_token(&line[i], &i, &type))) {
            if (!mx_check_token(temp, " \t\r\n\a")) {
                mx_push_func(&result, temp, type, shell);
            }
            else if (type != 0) {
                return mx_error_ush(type, result, line);
            }

            free(temp);
        }
    }

    mx_strdel(&line);
    mx_last_type(&result, amount);
    
    return result;
}
