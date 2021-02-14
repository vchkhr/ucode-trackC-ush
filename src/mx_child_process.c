#include "ush.h"

void mx_child_process(t_shell *shell, t_process *process, int job_id, int child) {
    if (isatty(STDIN_FILENO)) {
        mx_pgid(shell, job_id, child);
    }

    mx_job_dup(process);

    char **array = mx_strsplit(shell->jobs[job_id]->path, ':');
    char *command = process->arguments_amount[0];

    shell->jobs[job_id]->path = mx_path_check_process(array, command);
    mx_del_strarr(&array);

    char *error = mx_error_process(&shell->jobs[job_id]->path, command, &process->status);

    if (execve(shell->jobs[job_id]->path, process->arguments_amount, shell->jobs[job_id]->env) < 0) {
        mx_error_print(error, command);
        mx_printerr("\n");

        free(error);
        free(shell->jobs[job_id]->path);

        _exit(process->status);
    }

    free(shell->jobs[job_id]->path);
    free(error);
    
    exit(process->status);
}
