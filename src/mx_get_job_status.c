#include "ush.h"

int mx_get_job_status(t_shell *shell, int job, int status) {
    t_process *process;
    int flag = 0;

    if (job > 10000 || shell->jobs[job] == NULL) {
        return -1;
    }

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (process->status == status) {
            flag = 1;
        }
    }
    
    return flag;
}
