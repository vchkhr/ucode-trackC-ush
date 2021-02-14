#include "ush.h"

int mx_job_status(t_shell *shell, int job, int status) {
    if (job > 10000 || shell->jobs[job] == NULL) {
        return -1;
    }

    t_process *process;

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (process->status != 1) {
            process->status = status;
        }
    }

    return 0;
}
