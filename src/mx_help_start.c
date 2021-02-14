#include "ush.h"

void mx_help_start(t_shell *shell, t_job *job, int job_id, int status) {

    if (job->foregrd) {
        tcsetpgrp(STDIN_FILENO, job->pgid);

        if (status > 0) {
            status = mx_job_wait(shell, job_id);
        }
        else if (status == 0) {
            status = mx_job_wait(shell, job_id);
            shell->exit_code = status;
        }

        if (mx_job_completed(shell, job_id)) {
            mx_remove_job(shell, job_id);
        }

        signal(SIGTTOU, MX_SIG_IGN);
        tcsetpgrp(STDIN_FILENO, getpid());

        int terminal = STDIN_FILENO;
        
        tcgetattr(terminal, &job->tmodes);
        tcsetattr(terminal, TCSADRAIN, &shell->tmodes);
    }
    else {
        mx_print_pid(shell, job->job_id);
    }
}
