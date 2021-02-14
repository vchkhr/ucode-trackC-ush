#include "ush.h"

void mx_process_status(t_shell *shell, int pid, int status) {
    t_process *process;
    int job = mx_job_id_by_pid(shell, pid);

    for (int i = 1; i < shell->max_number_job; i++) {
        if (shell->jobs[i] == NULL) {
            continue;
        }

        for (process = shell->jobs[i]->first_pr; process != NULL; process = process->next) {
            if (process->pid == pid) {
                process->status = status;

                if (status == 2) {
                    if (shell->jobs_stack->previous && shell->jobs_stack->last) {
                        shell->jobs_stack->previous = shell->jobs_stack->last;
                    }

                    shell->jobs_stack->last = job;
                }
                
                break;
            }
        }
    }
}
