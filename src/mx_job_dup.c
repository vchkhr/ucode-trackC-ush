#include "ush.h"

void mx_job_dup(t_process *process) {
    if (process->r_infile[0] != STDIN_FILENO) {
        dup2(process->r_infile[0], STDIN_FILENO);
        close(process->r_infile[0]);
    }
    if (process->r_outfile[0] != STDOUT_FILENO) {
        dup2(process->r_outfile[0], STDOUT_FILENO);
        close(process->r_outfile[0]);
    }
    if (process->errfile != STDERR_FILENO) {
        dup2(process->errfile, STDERR_FILENO);
        close(process->errfile);
    }
}
