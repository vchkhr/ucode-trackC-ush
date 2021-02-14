#include "ush.h"

void mx_launch_jobs(t_shell *shell, t_ast **ast) {
    t_job *job = NULL;

    for (int i = 0; ast[i]; i++) {
        if ((job = mx_job_create(shell, ast[i]))) {
            job->job_type = mx_job_type(ast, i);
            
            mx_launch_job(shell, job);
        }
    }

    mx_clear_list_x3(&ast);
}
