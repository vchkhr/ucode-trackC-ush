#include "ush.h"

void mx_remove_job(t_shell *shell, int job) {
    if (job > 10000 || shell->jobs[job] == NULL) {
        return;
    }

    mx_job_destroy(shell, job);

    if (job == shell->max_number_job) {
        shell->max_number_job--;
    }
    
    shell->jobs[job] = NULL;
    mx_stack_pop(shell, job);
}
