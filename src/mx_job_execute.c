#include "ush.h"

void mx_job_execute(t_job *job) {
    extern char **environ;

    job->env = environ;
    job->path = getenv("PATH");

    if (!job->path) {
        job->path = "";
    }
}
