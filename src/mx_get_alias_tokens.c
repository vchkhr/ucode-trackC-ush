#include "ush.h"

char **mx_get_alias_tokens(char *string, t_shell *shell) {
    char **args = NULL;

    if (mx_strstr(string, "()")) {
        if (mx_get_functions(string, shell)) {
            return NULL;
        }
    }
    if (!mx_strncmp(string, "alias", 5) && string[5] && string[5] == ' ' && string[6] && !mx_isdelim(string[6], " \t\r\n\a")) {
        mx_get_aliases(string, shell);

        return NULL;
    }

    args = mx_tokens_parse(string);
    
    return args;
}
