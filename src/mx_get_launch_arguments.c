#include "ush.h"

char **mx_get_launch_arguments(t_process *process, int start) {
    char **arguments = (char **)malloc(sizeof(char *) * 256);
    int n = start;

    for (; process->arguments_amount[n] != NULL; n++) {
        arguments[n - start] = strdup(process->arguments_amount[n]);
    }

    mx_del_strarr(&process->arguments_amount);
    arguments[n - start] = NULL;

    return arguments;
}
