#include "ush.h"

void mx_pid_kill(t_shell *shell, t_process *process, int i) {
    pid_t pid = 0;

    if ((mx_pid_check(process->arguments_amount[i])) > 0) {
        mx_error_arguments(process->arguments_amount[0], ": illegal pid: ", process->arguments_amount[i], "\n");
        process->exit_code = 1;

        return;
    }
    else {
        pid = atoi(process->arguments_amount[i]);

        if (kill(pid, SIGTERM) < 0) {
            mx_error_arguments(process->arguments_amount[0], ": kill ", process->arguments_amount[i], " failed: no such process\n");
            process->exit_code = 1;
        }
        
        mx_process_status(shell, pid, 4);
    }
}
