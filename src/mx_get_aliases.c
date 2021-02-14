#include "ush.h"

void mx_get_aliases(char *string, t_shell *shell) {
    char **arguments = mx_tokens_parse(string);

    for (int i = 0; arguments[i]; i++) {
        char *name = NULL;
        char *value = NULL;

        mx_data_get_aliases(arguments[i], &name, &value);

        if (value && name && mx_strcmp(value, name)) {
            if (shell->aliases) {
                mx_set_variable(shell->aliases, name, value);
            }
            else  {
                mx_export_push(&shell->aliases, name, value);
            }
        }

        mx_strdel(&name);
        mx_strdel(&value);
    }
    
    free(arguments);
}
