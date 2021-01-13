#include "ush.h"

static int bg_get_job_id(t_shell *m_s, t_process *p) {
    int job_id;
    int n_args = 0;

    for (int i = 0; p->argv[i] != NULL; i++)
        n_args++;
    if (n_args > 2) {
        mx_printerr("ush: bg: too many arguments\n");
        return -1;
    }
    else if (n_args == 1) {
        if ((job_id = m_s->jobs_stack->last) < 1) {
            mx_printerr("bg: no current job\n");
            return -1;
        }
    }
    else {
        if ((job_id = mx_check_args(m_s, p)) < 1)
            return -1;
    }
    return job_id;
}

int mx_bg(t_shell *m_s, t_process *p) {
    pid_t pgid = 0;
    int job_id = 0;

    mx_set_last_job(m_s);
    if ((job_id = bg_get_job_id(m_s, p)) < 1)
        return 1;
    if ((pgid = mx_get_pgid_by_job_id(m_s, job_id)) < 1) {
        mx_err_j(p->argv[0], ": ", p->argv[1],": no such job\n");
        return 1;
    }
    if (kill(-pgid, SIGCONT) < 0) {
        mx_err_j(p->argv[0], ": job not found: ", p->argv[1], "\n");
        return 1;
    }
    mx_set_job_status(m_s, job_id, MX_STATUS_CONTINUED);
    mx_print_job_status(m_s, job_id, 0);
    return 0;
}

int mx_check_args(t_shell *m_s, t_process *p) {
    int job_id;

    if (p->argv[1][0] == '%' && isdigit(p->argv[1][1])) {
        if ((job_id = atoi((p->argv[1] + 1))) < 1) {
            mx_err_j(p->argv[0], ": ", p->argv[1],": no such job\n");
            return -1;
        }
    }
    else if (p->argv[1][0] == '%' && !isdigit(p->argv[1][1])) {
        if ((job_id = mx_g_find_job(m_s, (p->argv[1] + 1))) < 1) {
            mx_err_j(p->argv[0], ": job not found: ", (p->argv[1] + 1), "\n");
            return -1;
        }
    }
    else {
        if ((job_id = mx_g_find_job(m_s, p->argv[1])) < 1) {
            mx_err_j(p->argv[0], ": job not found: ", p->argv[1], "\n");
            return -1;
        }
    }
    return job_id;
}

void mx_err_j(char *arg0, char *arg1, char *arg2, char *arg3) {
    mx_printerr(arg0);
    mx_printerr(arg1);
    mx_printerr(arg2);
    mx_printerr(arg3);
}
