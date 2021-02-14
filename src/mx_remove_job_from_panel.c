#include "ush.h"

void mx_remove_job_from_panel(t_shell *shell, int job) {
    if (job > 10000 || shell->jobs[job] == NULL) {
        return;
    }
    
    if (job == shell->max_number_job) {
        shell->max_number_job--;
    }

    shell->jobs[job] = NULL;
    mx_stack_pop(shell, job);
}
