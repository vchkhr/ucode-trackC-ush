#include "ush.h"

void mx_redirects_in(t_shell *shell, t_job *job, t_process *process) {
    t_redir *redir;
    int i = 0;

    process->r_infile = (int *) realloc(process->r_infile, sizeof(int) * (process->c_input));
    process->r_infile[0] = job->infile;

    if (process->redirect) {
        for (redir = process->redirect; redir; redir = redir->next) {
            if (redir->input) {
                if (redir->delimiter == 5) {
                    shell->redir = mx_redirect_in(job, process, redir->input, i);
                }

                i++;
            }
        }
        
        job->infile = process->r_infile[0];
    }
}
