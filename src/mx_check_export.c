#include "ush.h"

void mx_check_export(char *argument, t_export *export, t_export *variables, int *result) {
    int flag = mx_check_id_export(argument);

    if (flag) {
        mx_error_print_export(argument, result);
    }
    else {
        char *name = NULL;
        char *value = NULL;

        mx_data_get_export(argument, &name, &value, variables);

        if (value != NULL) {
            setenv(name, value, 1);
        }

        mx_value_export(export, name, value);
        mx_value_export(variables, name, value);
        mx_data_clear(name, value);
        
        *result = 0;
    }
}
