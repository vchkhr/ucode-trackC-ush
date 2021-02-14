#include "ush.h"

int mx_check_arguments(t_shell *shell, t_process *process) {
    int pid;

    if (process->arguments_amount[1][0] == '%' && isdigit(process->arguments_amount[1][1])) {
        if ((pid = atoi((process->arguments_amount[1] + 1))) < 1) {
            mx_error_arguments(process->arguments_amount[0], ": ", process->arguments_amount[1],": no such job\n");
            
            return -1;
        }
    }
    else if (process->arguments_amount[1][0] == '%' && !isdigit(process->arguments_amount[1][1])) {
        if ((pid = mx_job_find(shell, (process->arguments_amount[1] + 1))) < 1) {
            mx_error_arguments(process->arguments_amount[0], ": job not found: ", (process->arguments_amount[1] + 1), "\n");
            
            return -1;
        }
    }
    else {
        if ((pid = mx_job_find(shell, process->arguments_amount[1])) < 1) {
            mx_error_arguments(process->arguments_amount[0], ": job not found: ", process->arguments_amount[1], "\n");
            
            return -1;
        }
    }
    
    return pid;
}
