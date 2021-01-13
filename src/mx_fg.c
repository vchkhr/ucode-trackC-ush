#include "ush.h"

static int fg_send_signal(t_shell *m_s, t_process *p, int pgid, int job_id) {
    int status;

    if (kill(-pgid, SIGCONT) < 0) {
        mx_err_j("fg", ": job not found: ", p->argv[1], "\n");
        return 1;
    }
    tcsetpgrp(STDIN_FILENO, pgid);
    mx_set_job_status(m_s, job_id, MX_STATUS_CONTINUED);
    mx_print_job_status(m_s, job_id, 0);
    status = mx_wait_job(m_s, job_id);
    if (mx_job_completed(m_s, job_id))
        mx_remove_job(m_s, job_id);
    signal(SIGTTOU, MX_SIG_IGN);
    tcsetpgrp(STDIN_FILENO, getpid());
    signal(SIGTTOU, MX_SIG_DFL);
    tcgetattr(STDIN_FILENO, &m_s->jobs[job_id]->tmodes);
    tcsetattr(STDIN_FILENO, TCSADRAIN, &m_s->jobs[job_id]->tmodes);
    return status;
}

static int fg_get_job_id (t_shell *m_s, t_process *p) {
    int job_id;
    int n_args = 0;

    for (int i = 0; p->argv[i] != NULL; i++)
        n_args++;
    if (n_args > 2) {
        mx_printerr("ush: fg: too many arguments\n");
        return -1;
    }
    else if (n_args == 1) {
        if ((job_id = m_s->jobs_stack->last) < 1) {
            mx_printerr("fg: no current job\n");
            return -1;
        }
    }
    else {
        if ((job_id = mx_check_args(m_s, p)) < 1)
            return -1;
    }
    return job_id;
}

int mx_fg(t_shell *m_s, t_process *p) {
    int status;
    pid_t pgid = 0;
    int job_id = 0;

    mx_set_last_job(m_s);
    if ((job_id = fg_get_job_id(m_s, p)) < 1)
        return 1;
    if ((pgid = mx_get_pgid_by_job_id(m_s, job_id)) < 1) {
        mx_err_j(p->argv[0], ": ", p->argv[1],": no such job\n");
        return 1;
    }
    status = fg_send_signal(m_s, p, pgid, job_id);
    return status;
}
