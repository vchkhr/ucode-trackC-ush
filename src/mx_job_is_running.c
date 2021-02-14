#include "ush.h"

int mx_job_is_running(t_shell *shell, int job) {
    t_process *process;
    int status = 0;

    if (job > 10000 || shell->jobs[job] == NULL) {
        return -1;
    }

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (process->status == 0) {
            status = 1;
        }
    }

    return status;
}
