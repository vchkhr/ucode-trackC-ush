#include "ush.h"

int mx_insert_job(t_shell *shell, t_job *job) {
    int id;

    if ((id = mx_get_next_job_id(shell)) < 0) {
        return -1;
    }

    job->job_id = id;
    shell->jobs[id] = job;

    mx_stack_push(shell, id);

    shell->max_number_job++;
    
    return id;
}
