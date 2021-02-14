#include "ush.h"

void mx_jobs_info(t_shell *shell, t_process *process, t_jobs jobs, int amount) {
    int job;

    for (int j = amount + 1; process->arguments_amount[j] != NULL; j++) {
        for (int i = shell->max_number_job; i > 0; i--) {
            if (shell->jobs[i] != NULL) {
                if ((job = mx_job_find(shell, (process->arguments_amount[j]))) < 1) {
                    mx_error_arguments(process->arguments_amount[0], ": job not found: ", process->arguments_amount[j], "\n");
                    process->exit_code = 1;

                    break;
                }

                mx_print_mask(shell, jobs, i);

                break;
            }
        }
    }
}
