#include "ush.h"

void mx_init_jobs_stack(t_shell *m_s) {
    t_stack *st = malloc(sizeof(t_stack));

    st->top = -1;
    st->last = -1;
    st->prev_last = -1;
    st->size = MX_JOBS_NUMBER;
    st->stack = malloc(sizeof(int) * MX_JOBS_NUMBER);
    for (int i = 0; i < st->size; i++)
        st->stack[i] = 0;
    m_s->jobs_stack = st;
}

void mx_push_to_stack(t_shell *m_s, int job) {
    if (m_s->jobs_stack->top < m_s->jobs_stack->size)
        m_s->jobs_stack->stack[++m_s->jobs_stack->top] = job;
}

void mx_pop_from_stack(t_shell *m_s, int job) {
    int j = 0;
    int i;
    int size = m_s->jobs_stack->size;
    int *temp = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        temp[i] = m_s->jobs_stack->stack[i];
    for (i = 0; i < size; i ++)
        m_s->jobs_stack->stack[i] = 0;
    if (m_s->jobs_stack->top >= 0) {
        for (i = 0; j < size; i++, j++) {
            if (temp[i] == job)
                i++;
            m_s->jobs_stack->stack[j] = temp[i];
        }
    }
    m_s->jobs_stack->top--;
    free(temp);
}

bool mx_get_from_stack(t_shell *m_s, int job_id) {
    if (m_s->jobs_stack->top >= 0) {
        if (job_id == m_s->jobs_stack->stack[m_s->jobs_stack->top])
            return true;
    }
    return false;
}

int mx_get_job_status(t_shell *m_s, int job_id, int status) {
    t_process *p;
    int flag = 0;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL)
        return -1;
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        if (p->status == status)
            flag = 1;
    }
    return flag;
}
