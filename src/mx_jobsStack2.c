#include "ush.h"

void mx_print_stack (t_shell *m_s) {
    int job_id;

    if (m_s->jobs_stack->top >= 0) {
        job_id = m_s->jobs_stack->stack[m_s->jobs_stack->top];
        for (int i = 0; i < m_s->jobs_stack->size; i++)
            printf("%d   ", m_s->jobs_stack->stack[i]);
        printf("\n");
    }
}

void mx_set_last_job(t_shell *m_s) {
    int size = m_s->jobs_stack->top;
    int last = -1;

    for (int i = size; i >= 0; i--) {
        if (mx_get_job_status(m_s, m_s->jobs_stack->stack[i], 2)) {
            last = m_s->jobs_stack->stack[i];
            break;
        }
    }
    if (last == -1) {
        for (int j = size; j >= 0; j--) {
            if ((mx_get_job_status(m_s, m_s->jobs_stack->stack[j], 0) > 0)
                && (m_s->jobs[m_s->jobs_stack->stack[j]]->foregrd == 0)) {
                last = m_s->jobs_stack->stack[j];
                break;
            }
        }
    }
    m_s->jobs_stack->last = last;
}

int mx_get_pgid_by_job_id(t_shell *m_s, int job_id) {
    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return -1;
    return m_s->jobs[job_id]->pgid;
}
