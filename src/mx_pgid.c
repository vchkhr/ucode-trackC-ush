#include "ush.h"

void mx_pgid(t_shell *shell, int job, int child) {
    if (shell->jobs[job]->pgid == 0) {
        shell->jobs[job]->pgid = child;
    }

    setpgid(child, shell->jobs[job]->pgid);

    if (shell->jobs[job]->foregrd) {
        tcsetpgrp(STDIN_FILENO, shell->jobs[job]->pgid);
    }
    
    signal(SIGINT, MX_SIG_DFL);
    signal(SIGQUIT, MX_SIG_DFL);
    signal(SIGTSTP, MX_SIG_DFL);
    signal(SIGTTIN, MX_SIG_DFL);
    signal(SIGTTOU, MX_SIG_DFL);
}
