#include "ush.h"

void mx_job_kill(t_shell *shell, t_process *process, int i) {
    int job;

    if ((job = mx_check_arguments(shell, process)) < 1) {
        process->exit_code = 1;

        return;
    }

    int pgid;

    if ((pgid = mx_get_pgid(shell, job)) < 1) {
        mx_error_arguments(process->arguments_amount[0], ": ", process->arguments_amount[i],": no such job\n");
        process->exit_code = 1;

        return;
    }
    if (kill(-pgid, SIGTERM) < 0) {
        mx_error_arguments(process->arguments_amount[0], ": job not found: ", process->arguments_amount[i], "\n");
        process->exit_code = 1;
    }
    
    mx_job_status(shell, job, 4);
}
