#include "ush.h"

t_job *mx_job_init(t_process *process) {
    t_job *job = (t_job *) malloc(sizeof(t_job));

    job->first_pr = process;
    job->foregrd = 1;

    for (; process != NULL; process = process->next) {
        if (!process->foregrd) {
            job->foregrd = 0;
        }
    }

    job->job_id = -1;
    job->pgid = 0;

    job->stdin = STDIN_FILENO;
    job->stdout = STDOUT_FILENO;
    job->stderr = STDERR_FILENO;

    job->infile = job->stdin;
    job->outfile = job->stdout;
    job->errfile = job->stderr;
    
    return job;
}
