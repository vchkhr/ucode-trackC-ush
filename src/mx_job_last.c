#include "ush.h"

void mx_job_last(t_shell *shell) {
    int size = shell->jobs_stack->first;
    int last = -1;

    for (int i = size; i >= 0; i--) {
        if (mx_get_job_status(shell, shell->jobs_stack->stack[i], 2)) {
            last = shell->jobs_stack->stack[i];

            break;
        }
    }

    if (last == -1) {
        for (int j = size; j >= 0; j--) {
            if ((mx_get_job_status(shell, shell->jobs_stack->stack[j], 0) > 0) && (shell->jobs[shell->jobs_stack->stack[j]]->foregrd == 0)) {
                last = shell->jobs_stack->stack[j];

                break;
            }
        }
    }
    
    shell->jobs_stack->last = last;
}
