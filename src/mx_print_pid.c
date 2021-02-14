#include "ush.h"

void mx_print_pid(t_shell *shell, int job) {
    t_process *process;

    if (job > 10000 || shell->jobs[job] == NULL) {
        mx_printstr("error job_id");
        mx_printstr("\n");
    }
    else {
        printf("[%d]", job);

        for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
            printf(" %d", process->pid);
        }
        
        printf("\n");
    }
}
