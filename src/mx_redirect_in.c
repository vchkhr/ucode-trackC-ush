#include "ush.h"

int mx_redirect_in(t_job *job, t_process *process, char *path, int j) {
    int status = 0;
    int fd;

    if ((fd = open(path, O_RDONLY, 0666)) < 0) {
        mx_printerr("ush :");
        perror(path);

        status = 1;
        job->exit_code = 1;

        return status;
    }

    process->r_infile[j] = fd;

    return status;
}
