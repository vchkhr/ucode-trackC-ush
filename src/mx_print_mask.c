#include "ush.h"

void mx_print_mask(t_shell *shell, t_jobs jobs, int i) {
    if (jobs.right && !jobs.stop) {
        if (shell->jobs[i] != NULL && mx_job_is_running(shell, i)) {
            mx_jod_status_print(shell, i, jobs.left);
        }
    }
    else if (jobs.stop && !jobs.right) {
        if (shell->jobs[i] != NULL && !mx_job_is_running(shell, i)) {
            mx_jod_status_print(shell, i, jobs.left);
        }
    }
    else {
        if (shell->jobs[i] != NULL) {
            mx_jod_status_print(shell, i, jobs.left);
        }
    }
}
