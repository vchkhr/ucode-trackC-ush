#include "ush.h"

int mx_get_next_job_id(t_shell *m_s) {
    for (int i = 1; i < m_s->max_number_job + 1; i++) {
        if (m_s->jobs[i] == NULL)
            return i;
    }
    return -1;
}

int mx_insert_job(t_shell *m_s, t_job *job) {
    int id;

    if ((id = mx_get_next_job_id(m_s)) < 0)
        return -1;
    job->job_id = id;
    m_s->jobs[id] = job;
    mx_push_to_stack(m_s, id);
    m_s->max_number_job++;
    return id;
}

void mx_remove_job(t_shell *m_s, int job_id) {
    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return;
    mx_destroy_jobs(m_s, job_id);
    if (job_id == m_s->max_number_job)
        m_s->max_number_job--;
    m_s->jobs[job_id] = NULL;
    mx_pop_from_stack(m_s, job_id);
}

void mx_remove_job_from_panel(t_shell *m_s, int job_id) {
    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return;
    if (job_id == m_s->max_number_job)
        m_s->max_number_job--;
    m_s->jobs[job_id] = NULL;
    mx_pop_from_stack(m_s, job_id);
}

int mx_job_id_by_pid(t_shell *m_s, int pid) {
    int i;
    t_process *p;

    for (i = 1; i <= m_s->max_number_job + 1; i++) {
        if (m_s->jobs[i] != NULL) {
            for (p = m_s->jobs[i]->first_pr; p != NULL; p = p->next) {
                if (p->pid == pid) {
                    return i;
                }
            }
        }
    }
    return -1;
}

