#include "ush.h"

static int count_args(char **args) {
    int n_args = 0;

    for (int i = 1; args[i] != NULL; i++)
        n_args++;
    return n_args;
}

static int check_pid(char *s) {
    for (int j = 0; s[j] != '\0'; j++) {
        if (!(mx_isdigit(s[j]))) {
            return 1;
        }
    }
    return 0;
}

static void kill_job(t_shell *m_s, t_process *p, int i) {
    int job_id;
    int pgid;

    if ((job_id = mx_check_args(m_s, p)) < 1) {
        p->exit_code = 1;
        return;
    }
    if ((pgid = mx_get_pgid_by_job_id(m_s, job_id)) < 1) {
        mx_err_j(p->argv[0], ": ", p->argv[i],": no such job\n");
        p->exit_code = 1;
        return;
    }
    if (kill(-pgid, SIGTERM) < 0) {
        mx_err_j(p->argv[0], ": job not found: ", p->argv[i], "\n");
        p->exit_code = 1;
    }
    mx_set_job_status(m_s, job_id, MX_STAT_TERMINATED);
}

static void kill_pid(t_shell *m_s, t_process *p, int i) {
    pid_t pid = 0;

    if ((check_pid(p->argv[i])) > 0) {
        mx_err_j(p->argv[0], ": illegal pid: ", p->argv[i], "\n");
        p->exit_code = 1;
        return;
    }
    else {
        pid = atoi(p->argv[i]);
        if (kill(pid, SIGTERM) < 0) {
            mx_err_j(p->argv[0], ": kill ", p->argv[i],
                     " failed: no such process\n");
            p->exit_code = 1;
        }
        mx_set_process_status(m_s, pid, MX_STAT_TERMINATED);
    }
}

int mx_kill(t_shell *m_s, t_process *p) {
    p->exit_code = 0;
    int n_args = 0;

    n_args = count_args(p->argv);
    mx_set_last_job(m_s);
    if (n_args == 0) {
        mx_printerr("ush: kill: not enough arguments\n");
        p->exit_code = 1;
    }
    if (n_args) {
        for (int i = 1; i <= n_args; i++) {
            if (p->argv[i][0] == '%')
                kill_job(m_s, p, i);
            else
                kill_pid(m_s, p, i);
        }
    }
    return p->exit_code;
}
