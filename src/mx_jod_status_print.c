#include "ush.h"

void mx_jod_status_print(t_shell *shell, int job, int flag) {
    const char *status[] = {"running", "done", "suspended", "continued", "terminated"};

    printf("[%d] ", job);

    if (shell->jobs_stack->last == job) {
        printf("%2c ", 43);
    }
    else if (shell->jobs_stack->previous == job) {
        printf("%2c ", 45);
    }
    else {
        printf("%2c ", ' ');
    }

    t_process *process;

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (flag) {
            printf("%d ", process->pid);
        }
        else {
            printf("");
        }

        printf("%s", status[process->status]);

        int length = mx_strlen(status[process->status]);
        
        mx_print_spaces(MAX_LEN + 1 - length);
        mx_print_arguments(process->arguments_amount, " ");

        if (process->next != NULL) {
            mx_printstr(" |\n       ");
        }
        else {
            mx_printstr("\n");
        }
    }
}
