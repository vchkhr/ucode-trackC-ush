#include "ush.h"

int mx_proccess_launch(t_shell *shell, t_process *process, int job) {
    pid_t child_pid = fork();
    int interactive = isatty(STDIN_FILENO);

    process->status = 0;
    
    if (child_pid < 0) {
        perror("error fork");

        exit(1);
    }
    else if (child_pid == 0) {
        mx_child_process(shell, process, job, child_pid);
    }
    else {
        process->pid = child_pid;

        if (interactive) {
            pid_t pid = child_pid;

            if (shell->jobs[job]->pgid == 0) {
                shell->jobs[job]->pgid = pid;
            }

            setpgid(pid, shell->jobs[job]->pgid);
        }
    }
    
    return process->status >> 8;
}
