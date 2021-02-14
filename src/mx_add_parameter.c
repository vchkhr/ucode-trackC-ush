#include "ush.h"

int mx_add_parameter(char *parameter, t_export **environment, char option) {
    char *string;

    if (parameter) {
        if (option == 'u' && strchr(parameter, '=')) {
            mx_printerr("env: unsetenv ");
            mx_printerr(parameter);
            mx_printerr(": Invalid argument\n");

            return -1;
        }

        string = mx_get_option(option);
        mx_export_push(environment, string, parameter);
        
        free(parameter);
        free(string);

        return 0;
    }
    else {
        mx_error_print_environment(option, "env: option requires an argument -- ");
        
        return -1;
    }
}
