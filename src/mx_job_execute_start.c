#include "ush.h"

int mx_job_execute_start(t_shell *shell, t_job *job, int job_id) {
    t_process *process;
    int pipe[2];

    mx_job_execute(job);

    for (process = shell->jobs[job_id]->first_pr; process; process = process->next) {
        mx_check_exit(shell, process);

        if ((mx_redirections(shell, job, process)) != 0) {
            process->status = 1;
            process->exit_code = 1;

            continue;
        }
        if (process->pipe) {
            mx_pipe(shell, job, pipe, job_id);
            process->r_outfile[0] = job->outfile;
        }

        mx_job_help(shell, job, process, job_id);
        job->infile = pipe[0];
    }

    mx_help_start(shell, job, job_id, job->exit_code);
    
    return job->exit_code;
}
