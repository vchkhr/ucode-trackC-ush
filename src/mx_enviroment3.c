#include "ush.h"

int mx_count_env_options(char **args, t_env_builtin *env) {
    int n_options = 0;

    for (int i = 1; args[i] != NULL; i++) {
        if (args[i][0] != '-') break;
        if (strcmp(args[i], "--") == 0) {
            n_options++;
            break;
        }
        int valid_arg = mx_add_option(args, &i, &n_options, env);
        if (valid_arg < 0)
            return -1;
        n_options++;
    }
    return n_options;
}

void mx_env_err(int *flag, int *exit_code, char option) {
    mx_print_env_error(option, "env: illegal option -- ");
    (*exit_code) = -1;
    (*flag)--;
}

void mx_print_env_error(char option, char *error) {
    mx_printerr(error);
    write(2, &option, 1);
    mx_printerr("\nusage: env [-iv] [-P utilpath] [-u name]\n");
    mx_printerr("           [name=value ...] [utility [argument ...]]\n");
}
