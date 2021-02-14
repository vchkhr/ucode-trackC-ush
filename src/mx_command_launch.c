#include "ush.h"

void mx_command_launch(t_process *process, t_default *environment, int *result) {
    char **arguments = mx_get_launch_arguments(process, environment->options + environment->variables + 1);
    char **array = mx_get_environment(environment->list);

    if (!environment->path) {
        environment->path = strdup(getenv("PATH"));
    }
    
    process->arguments_amount = arguments;
    *result = mx_bin_start(process, environment->path, array);
    
    mx_del_strarr(&array);
}
