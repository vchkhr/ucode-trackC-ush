#include "ush.h"

int mx_job_id_by_pid(t_shell *shell, int pid) {
    t_process *process;

    for (int i = 1; i <= shell->max_number_job + 1; i++) {
        if (shell->jobs[i] != NULL) {
            for (process = shell->jobs[i]->first_pr; process != NULL; process = process->next) {
                if (process->pid == pid) {
                    return i;
                }
            }
        }
    }
    
    return -1;
}
