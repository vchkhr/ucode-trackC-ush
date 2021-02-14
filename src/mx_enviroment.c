#include "ush.h"

int mx_environment(t_shell *shell, t_process *process) {
    t_default *environment = mx_initialise_environment(process);
    int result = 0;

    mx_data_set(environment, process->arguments_amount);

    if (environment->options < 0 || environment->variables < 0) {
        result = 1;
    }
    else if (environment->arguments == 0) {
        mx_environment_print(environment->list);
    }
    else {
        mx_command_launch(process, environment, &result);
    }
    
    if (environment->path) {
        free(environment->path);
    }

    shell->result = 0;

    mx_export_clear(environment->list);
    mx_export_clear(environment->parameters);

    free(environment);

    return result;
}
