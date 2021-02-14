#include "ush.h"

int mx_pid(t_shell *shell, t_process *process) {
    pid_t pgid = 0;
    int job = 0;
    
    mx_job_last(shell);

    if ((job = mx_get_bg_job_id(shell, process)) < 1) {
        return 1;
    }
    if ((pgid = mx_get_pgid(shell, job)) < 1) {
        mx_error_arguments(process->arguments_amount[0], ": ", process->arguments_amount[1],": no such job\n");

        return 1;
    }
    if (kill(-pgid, SIGCONT) < 0) {
        mx_error_arguments(process->arguments_amount[0], ": job not found: ", process->arguments_amount[1], "\n");

        return 1;
    }

    mx_job_status(shell, job, 3);
    mx_jod_status_print(shell, job, 0);

    return 0;
}
