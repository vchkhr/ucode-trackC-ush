#include "ush.h"

void mx_redirects_out(t_shell *shell, t_job *job, t_process *process) {
    t_redir *redir;
    int i = 0;

    process->r_outfile[0] = job->outfile;

    if (process->redirect) {
        for (redir = process->redirect; redir; redir = redir->next) {
            if (redir->output) {
                int flags = mx_flag_redirect(redir->delimiter);
                int fd = open(redir->output, flags, 0666);

                if (fd < 0) {
                    mx_printerr("ush :");
                    perror(redir->output);

                    shell->redir = 1;

                    continue;
                }
                
                process->r_outfile[i] = fd;
                lseek(process->r_outfile[i], 0, SEEK_END);
                i++;
            }
        }
    }

    job->outfile = process->r_outfile[0];
}
