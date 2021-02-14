#include "ush.h"

int mx_fg(t_shell *shell, t_process *process) {
    pid_t pgid = 0;
    int job = 0;

    mx_job_last(shell);

    if ((job = mx_job_id_get(shell, process)) < 1) {
        return 1;
    }

    if ((pgid = mx_get_pgid(shell, job)) < 1) {
        mx_error_arguments(process->arguments_amount[0], ": ", process->arguments_amount[1],": no such job\n");

        return 1;
    }

    return mx_signal_send(shell, process, pgid, job);
}
