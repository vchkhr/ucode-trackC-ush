#include "ush.h"

static char *get_option(char c) {
    char *option = malloc(2);

    option[0] = c;
    option[1] = '\0';
    return option;
}

static int add_param(char *param, t_export **env_params, char option) {
    char *str_option;

    if (param) {
        if (option == 'u' && strchr(param, '=')) {
            mx_printerr("env: unsetenv ");
            mx_printerr(param);
            mx_printerr(": Invalid argument\n");
            return -1;
        }
        str_option = get_option(option);
        mx_push_export(env_params, str_option, param);
        free(param);
        free(str_option);
        return 0;
    }
    else {
        mx_print_env_error(option, "env: option requires an argument -- ");
        return -1;
    }
}

static char *get_parameter (char **args, int *i, int j, int *n_options) {
    char *param = NULL;

    if(args[*i][j + 1] != '\0') {
        param = mx_strdup_from(args[*i], j);
    }
    else if (args[*i + 1]) {
        param = strdup(args[*i + 1]);
        (*n_options)++;
        (*i)++;
    }
    return param;
}

int mx_add_option(char **args, int *i, int *n_options, t_env_builtin *env) {
    int exit_code = 0;
    char option;
    char *param = NULL;
    int flag = 1;

    for (int j = 1; j <= mx_strlen(args[*i]) && flag; j++) {
        option = args[*i][j];
        if (args[*i][j] == 'u' || args[*i][j] == 'P') {
            param = get_parameter(args, i, j, n_options);
            exit_code = add_param(param, &env->env_params, option);
            flag--;
        }
        else if (args[*i][j] == 'i' || args[*i][j] == '-'
                 || mx_strlen(args[*i]) == 1)
            env->env_options.i = 1;
        else if (j != mx_strlen(args[*i]))
            mx_env_err(&flag, &exit_code, option);
    }
    return exit_code;
}
