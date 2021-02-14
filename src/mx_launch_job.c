#include "ush.h"

void mx_launch_job(t_shell *shell, t_job *job) {
    setbuf(stdout, NULL);

    int status = 0;
    int job_id = mx_insert_job(shell, job);

    mx_job_check(shell);

    if (!job->job_type) {
        status = mx_job_execute_start(shell, job, job_id);
    }
    else if (job->job_type == 2 && shell->exit_code == 0) {
        status = mx_job_execute_start(shell, job, job_id);
    }
    else if (job->job_type == 3 && shell->exit_code != 0) {
        status = mx_job_execute_start(shell, job, job_id);
    }
    else {
        mx_remove_job(shell, job_id);
    }

    if (!shell->exit_code) {
        shell->exit_code = status;
    }

    char *result = mx_itoa(shell->exit_code);

    mx_set_variable(shell->variables, "?", result);
    free(result);
}
