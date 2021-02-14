#include "ush.h"

void mx_pipe(t_shell *shell, t_job *job, int mypipe[2], int job_id) {
    if (pipe(mypipe) < 0) {
        perror("pipe");
        mx_remove_job(shell, job_id);

        exit(1);
    }
    
    job->outfile = mypipe[1];
}
