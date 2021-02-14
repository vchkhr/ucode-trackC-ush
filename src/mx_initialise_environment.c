#include "ush.h"

t_default *mx_initialise_environment(t_process *process) {
    t_default *environment = (t_default *)malloc(sizeof(t_default));

    environment->parameters = NULL;
    environment->list = NULL;
    environment->environment_options.i = 0;
    environment->environment_options.u = 0;
    environment->environment_options.P = 0;
    environment->options = mx_count_environment_options(process->arguments_amount, environment);
    environment->variables = mx_vars_count(process->arguments_amount, environment->options);
    environment->arguments = mx_count_arguments(process->arguments_amount, environment->variables + environment->options);
    environment->path = NULL;
    
    return environment;
}
