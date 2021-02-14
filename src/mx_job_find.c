#include "ush.h"

int mx_job_find(t_shell *shell, char *argument) {
    t_process *process;

    for (int i = shell->jobs_stack->first, a; i >= 0 ; i--) {
        a = shell->jobs_stack->stack[i];

        if (shell->jobs[a] == NULL) {
            continue;
        }

        for (process = shell->jobs[a]->first_pr; process != NULL; process = process->next) {
            if ((strncmp(process->arguments_amount[0], argument, strlen(argument))) == 0) {
                return a;
            }
        }
    }
    
    return -1;
}
