#include "ush.h"

int mx_kill(t_shell *shell, t_process *process) {
    process->exit_code = 0;
    int amount = mx_arguments_count_kill(process->arguments_amount);

    mx_job_last(shell);

    if (amount == 0) {
        mx_printerr("ush: kill: not enough arguments\n");

        process->exit_code = 1;
    }
    if (amount) {
        for (int i = 1; i <= amount; i++) {
            if (process->arguments_amount[i][0] == '%') {
                mx_job_kill(shell, process, i);
            }
            else {
                mx_pid_kill(shell, process, i);
            }
        }
    }
    
    return process->exit_code;
}
