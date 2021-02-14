#include "ush.h"

int mx_get_bg_job_id(t_shell *shell, t_process *process) {
    int job;
    int amount = 0;

    for (int i = 0; process->arguments_amount[i] != NULL; i++) {
        amount++;
    }

    if (amount > 2) {
        mx_printerr("ush: bg: too many arguments\n");

        return -1;
    }
    else if (amount == 1) {
        if ((job = shell->jobs_stack->last) < 1) {
            mx_printerr("bg: no current job\n");

            return -1;
        }
    }
    else {
        if ((job = mx_check_arguments(shell, process)) < 1) {
            return -1;
        }
    }
    
    return job;
}
