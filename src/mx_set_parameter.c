#include "ush.h"

int mx_set_parameter(char **arguments, t_shell *shell) {
    char *name;
    char *value;

    for (int i = 0; arguments[i] != NULL; i++) {
        name = NULL;
        value = NULL;

        mx_data_get_set_parameter(arguments[i], &name, &value);

        if (value != NULL && name != NULL) {
            mx_set_variable(shell->variables, name, value);
            mx_export_parameter(shell->exported, name, value);
        }

        if (name) {
            free(name);
        }
        if (value) {
            free(value);
        }
    }
    
    return 0;
}
