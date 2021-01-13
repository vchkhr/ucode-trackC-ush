#include "ush.h"

static t_job *init_job(t_process *first_p) {
    t_job *new_job = (t_job *) malloc(sizeof(t_job));

    new_job->first_pr = first_p;
    new_job->foregrd = MX_FOREGROUND;
    for (; first_p != NULL; first_p = first_p->next)
        if (!first_p->foregrd)
            new_job->foregrd = MX_BACKGROUND;
    new_job->job_id = -1;
    new_job->pgid = 0;
    new_job->stdin = STDIN_FILENO;
    new_job->stdout = STDOUT_FILENO;
    new_job->stderr = STDERR_FILENO;
    new_job->infile = new_job->stdin;
    new_job->outfile = new_job->stdout;
    new_job->errfile = new_job->stderr;
    return new_job;
}

t_job *mx_create_job(t_shell *m_s, t_ast *list) {
    t_process *first_p = NULL;

    for (t_ast *l = list; l; l = l->next) {
        if ((l->args = mx_filters(l->token, m_s)) && *(l->args))
            mx_push_process_back(&first_p, m_s, l);
        else {
            mx_clear_process(first_p);
            return NULL;
        }
    }
    return init_job(first_p);
}
