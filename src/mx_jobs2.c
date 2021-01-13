#include "ush.h"

int mx_set_job_status(t_shell *m_s, int job_id, int status) {
    t_process *p;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return -1;
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        if (p->status != MX_STATUS_DONE)
            p->status = status;
    }
    return 0;
}

int mx_job_completed(t_shell *m_s, int job_id) {
    t_process *p;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return -1;
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        if (p->status != MX_STATUS_DONE && p->status != MX_STAT_TERMINATED) {
            return 0;
        }
    }
    return 1;
}

int mx_job_is_running(t_shell *m_s, int job_id) {
    t_process *p;
    int status = 0;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return -1;
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        if (p->status == MX_STATUS_RUNNING)
            status = 1;
    }
    return status;
}

int mx_g_find_job(t_shell *m_s, char *arg) {
    int i;
    int a;
    t_process *p;

    for (i = m_s->jobs_stack->top; i >= 0 ; i--) {
        a = m_s->jobs_stack->stack[i];
        if (m_s->jobs[a] == NULL)
            continue;
        for (p = m_s->jobs[a]->first_pr; p != NULL; p = p->next) {
            if ((strncmp(p->argv[0], arg, strlen(arg))) == 0)
                return a;
        }
    }
    return -1;
}

void mx_destroy_jobs(t_shell *m_s, int id) {
    t_process *p;

    for (p = m_s->jobs[id]->first_pr; p != NULL; p = p->next) {
        mx_clear_process(p);
    }
    free(m_s->jobs[id]);
}
