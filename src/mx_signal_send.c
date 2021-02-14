#include "ush.h"

int mx_signal_send(t_shell *shell, t_process *process, int pgid, int job) {
    if (kill(-pgid, SIGCONT) < 0) {
        mx_error_arguments("fg", ": job not found: ", process->arguments_amount[1], "\n");

        return 1;
    }

    tcsetpgrp(STDIN_FILENO, pgid);
    mx_job_status(shell, job, 3);
    mx_jod_status_print(shell, job, 0);

    int status = mx_job_wait(shell, job);

    if (mx_job_completed(shell, job)) {
        mx_remove_job(shell, job);
    }

    signal(SIGTTOU, MX_SIG_IGN);
    tcsetpgrp(STDIN_FILENO, getpid());
    signal(SIGTTOU, MX_SIG_DFL);

    tcgetattr(STDIN_FILENO, &shell->jobs[job]->tmodes);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &shell->jobs[job]->tmodes);
    
    return status;
}
