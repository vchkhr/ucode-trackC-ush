#include "ush.h"

void mx_job_destroy(t_shell *shell, int id) {
    t_process *process;

    for (process = shell->jobs[id]->first_pr; process != NULL; process = process->next) {
        mx_process_clear(process);
    }
    
    free(shell->jobs[id]);
}
