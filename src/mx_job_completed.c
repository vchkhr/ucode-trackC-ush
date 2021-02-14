#include "ush.h"

int mx_job_completed(t_shell *shell, int job) {
    if (job > 10000 || shell->jobs[job] == NULL) {
        return -1;
    }

    t_process *process;

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (process->status != 1 && process->status != 4) {
            return 0;
        }
    }
    
    return 1;
}
