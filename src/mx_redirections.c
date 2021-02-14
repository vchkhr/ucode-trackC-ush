#include "ush.h"

int mx_redirections(t_shell *shell, t_job *job, t_process *process) {
    mx_redirects_count(process);
    shell->redir = 0;

    mx_redirects_in(shell, job, process);
    mx_redirects_out(shell, job, process);
    process->errfile = job->errfile;

    if (shell->redir == 1) {
        shell->exit_code = 1;
        job->exit_code = 1;
        mx_set_variable(shell->variables, "?", "1");
    }
    
    return shell->redir;
}
