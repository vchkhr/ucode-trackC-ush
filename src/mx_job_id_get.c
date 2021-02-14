#include "ush.h"

int mx_job_id_get(t_shell *shell, t_process *process) {
    int job_id;
    int amount = 0;

    for (int i = 0; process->arguments_amount[i] != NULL; i++) {
        amount++;
    }

    if (amount > 2) {
        mx_printerr("ush: fg: too many arguments\n");

        return -1;
    }
    else if (amount == 1) {
        job_id = shell->jobs_stack->last;

        if (job_id < 1) {
            mx_printerr("fg: no current job\n");

            return -1;
        }
    }
    else {
        job_id = mx_check_arguments(shell, process);

        if (job_id < 1) {
            return -1;
        }
    }
    
    return job_id;
}
