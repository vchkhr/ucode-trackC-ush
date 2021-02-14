#include "ush.h"

void mx_job_help(t_shell *shell, t_job *job, t_process *process, int job_id) {
    process->infile = job->infile;
    process->outfile = job->outfile;
    process->errfile = job->errfile;
    job->flag = 0;

    if (!process->pipe) {
        job->flag = mx_flag_get(process->arguments_amount);
    }
    if (job->flag) {
        job->exit_code = mx_set_parameter(process->arguments_amount, shell);
        mx_remove_job(shell, job_id);
    }
    else if (process->type != -1) {
        job->exit_code = mx_builting_start(shell, process, job_id);
    }
    else {
        job->exit_code = mx_proccess_launch(shell, process, job_id);
    }

    if (job->infile != job->stdin) {
        close(job->infile);
    }
    if (job->outfile != job->stdout) {
        close(job->outfile);
    }
    
    shell->exit_code = job->exit_code;
}
