#include "ush.h"

void mx_default_fork(t_shell *shell, int job_id, int (*functions[]) (t_shell *shell, t_process *process), t_process *process) {
    pid_t child = fork();
    process->pid = child;
    
    if (child < 0) {
        perror("error fork");

        exit(1);
    }
    else if (child == 0) {
        if (isatty(STDIN_FILENO)) {
            mx_pgid(shell, job_id, child);
        }

        mx_job_dup(process);
        process->exit_code = functions[process->type](shell, process);

        exit(process->exit_code);
    }
    else {
        if (isatty(STDIN_FILENO)) {
            if (shell->jobs[job_id]->pgid == 0) {
                shell->jobs[job_id]->pgid = child;
            }
            
            setpgid (child, shell->jobs[job_id]->pgid);
        }
    }
}
