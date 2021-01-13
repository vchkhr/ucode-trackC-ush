#include "ush.h"

static int count_args(char **args, int n_options) {
    int n_args = 0;

    for (int i = n_options + 1; args[i] != NULL; i++) {
        n_args++;
    }
    return n_args;
}

static void fill_options(int n_options, t_jobs *jobs_op, char **args) {
    for (int i = n_options; i > 0; i--) {
        for (int j = mx_strlen(args[i]); j > 0; j--) {
            if (args[i][j] == 'l')
                jobs_op->l = 1;
            if (args[i][j] == 'r')
                jobs_op->r = 1;
            if (args[i][j] == 's')
                jobs_op->s = 1;
        }
    }
}

static void print_jobs_by_mask(t_shell *m_s, t_jobs jobs_op, int i) {
    if (jobs_op.r && !jobs_op.s) {
        if (m_s->jobs[i] != NULL && mx_job_is_running(m_s, i))
            mx_print_job_status(m_s, i, jobs_op.l);
    }
    else if (jobs_op.s && !jobs_op.r) {
        if (m_s->jobs[i] != NULL && !mx_job_is_running(m_s, i))
            mx_print_job_status(m_s, i, jobs_op.l);
    }
    else {
        if (m_s->jobs[i] != NULL)
            mx_print_job_status(m_s, i, jobs_op.l);
    }
}

static void help_jobs(t_shell *m_s, t_process *p, t_jobs jobs_op, int n_opt) {
    int job_id;

    for (int j = n_opt + 1; p->argv[j] != NULL; j++) {
        for (int i = m_s->max_number_job; i > 0; i--) {
            if (m_s->jobs[i] != NULL) {
                if ((job_id = mx_g_find_job(m_s, (p->argv[j]))) < 1) {
                    mx_err_j(p->argv[0], ": job not found: ",
                             p->argv[j], "\n");
                    p->exit_code = 1;
                    break;
                }
                print_jobs_by_mask(m_s, jobs_op, i);
                break;
            }
        }
    }
}

int mx_jobs(t_shell *m_s, t_process *p) {
    t_jobs jobs_op = {0, 0, 0};
    int n_opt;
    int n_args;

    p->exit_code = 0;
    if ((n_opt = mx_count_options(p->argv, "lrs", "jobs", " [-lrs]")) < 0) {
        p->exit_code = 1;
        return p->exit_code;
    }
    n_args = count_args(p->argv, n_opt);
    mx_set_last_job(m_s);
    fill_options(n_opt, &jobs_op, p->argv);
    if (n_opt >= 0 && n_args == 0) {
        for (int i = 0; i < MX_JOBS_NUMBER; i++)
            print_jobs_by_mask(m_s, jobs_op, i);
    }
    else if (n_args)
        help_jobs(m_s, p, jobs_op, n_opt);
    return p->exit_code;
}

