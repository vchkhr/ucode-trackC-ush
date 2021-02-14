#include "ush.h"

void mx_process_bin(t_process *process, char *path, char **environment, int *status) {
    char *const *envp =  environment;
    char **arrays = mx_strsplit(path, ':');
    char *command = process->arguments_amount[0];
    char *error;

    path  = mx_path_check_bin(arrays, command);

    if (!path) {
        path = strdup(command);
    }

    error = mx_error_bin(&path, command, status);

    if (execve(path, process->arguments_amount, envp) < 0) {
        mx_error_print_bin(command, error);
        _exit(*status);
    }
    
    exit(0);
}
