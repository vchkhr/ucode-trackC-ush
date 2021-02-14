#include "ush.h"

int mx_option_add(char **arguments, int *n, int *amount, t_default *environment) {
    int result = 0;

    for (int i = 1, flag = 1; i <= mx_strlen(arguments[*n]) && flag; i++) {
        char option = arguments[*n][i];

        if (arguments[*n][i] == 'u' || arguments[*n][i] == 'P') {
            char *param = mx_get_parameter(arguments, n, i, amount);
            
            result = mx_add_parameter(param, &environment->parameters, option);
            flag--;
        }
        else if (arguments[*n][i] == 'i' || arguments[*n][i] == '-' || mx_strlen(arguments[*n]) == 1) {
            environment->environment_options.i = 1;
        }
        else if (i != mx_strlen(arguments[*n])) {
            mx_environment_error(&flag, &result, option);
        }
    }
    
    return result;
}
