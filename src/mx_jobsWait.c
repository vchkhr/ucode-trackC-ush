#include "ush.h"

void mx_check_jobs(t_shell *m_s) {
    int status;
    pid_t pid;
    int job_id;

    while ((pid = waitpid(-1, &status, MX_WNOHANG | MX_WUNTRACED
           | MX_WCONTINUED)) > 0) {
        if (MX_WIFEXITED(status))
            mx_set_process_status(m_s, pid, MX_STATUS_DONE);
        else if (MX_WIFSTOPP(status))
            mx_set_process_status(m_s, pid, MX_STATUS_SUSPENDED);
        else if (MX_WIFCONT(status)) {
            mx_set_process_status(m_s, pid, MX_STATUS_CONTINUED);
        }
        job_id = mx_job_id_by_pid(m_s, pid);
        if (job_id > 0 && mx_job_completed(m_s, job_id)) {
            mx_print_job_status(m_s, job_id, 0);
            mx_remove_job(m_s, job_id);
        }
    }
}

int mx_wait_job(t_shell *m_s, int job_id) {
    int proc_count;
    int wait_pid = -1;
    int wait_count = 0;
    int status = 0;

   proc_count = mx_get_proc_count(m_s, job_id, MX_FILT_IN_PROGR);
    while (wait_count < proc_count) {
        wait_pid = waitpid(-m_s->jobs[job_id]->pgid, &status, MX_WUNTRACED);
        wait_count++;
        if (MX_WIFEXITED(status))
            mx_set_process_status(m_s, wait_pid, MX_STATUS_DONE);
        else if (MX_WIFSIGNALED(status))
            mx_set_process_status(m_s, wait_pid, MX_STAT_TERMINATED);
        else if (MX_WSTOPSIG(status)) {
            mx_set_process_status(m_s, wait_pid, MX_STATUS_SUSPENDED);
            if (wait_count == proc_count)
                mx_print_job_status(m_s, job_id, 0);
        }
    }
    return status >> 8;
}

int mx_get_proc_count(t_shell *m_s, int job_id, int filter) {
    t_process *p;
    int count = 0;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL) {
        return -1;
    }
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        if (filter == MX_FILTER_ALL
            || (filter == MX_FILTER_DONE && p->status == MX_STATUS_DONE)
            || (filter == MX_FILT_IN_PROGR && p->status != MX_STATUS_DONE)) {
            count++;
        }
    }
    return count;
}

void mx_set_process_status(t_shell *m_s, int pid, int status) {
    int i;
    t_process *p;
    int job_id = mx_job_id_by_pid(m_s, pid);

    for (i = 1; i < m_s->max_number_job; i++) {
        if (m_s->jobs[i] == NULL)
            continue;
        for (p = m_s->jobs[i]->first_pr; p != NULL; p = p->next) {
            if (p->pid == pid) {
                p->status = status;
                if (status == MX_STATUS_SUSPENDED) {
                    if (m_s->jobs_stack->prev_last && m_s->jobs_stack->last)
                        m_s->jobs_stack->prev_last = m_s->jobs_stack->last;
                    m_s->jobs_stack->last = job_id;
                }
                break;
            }
        }
    }
}
