#include "ush.h"

static void print_spaces(int number) {
    for (int i = 0; i < number; i++) {
        mx_printchar(' ');
    }
}

void mx_print_job_status(t_shell *m_s, int job_id, int flag) {
    t_process *p;
    int len;
    const char* status[] = {"running", "done", "suspended",
                             "continued", "terminated"};

    printf("[%d] ", job_id);
    if (m_s->jobs_stack->last == job_id)
        printf("%2c ", 43);  // Print +
    else if (m_s->jobs_stack->prev_last == job_id)
        printf("%2c ", 45);  // Print -
    else
        printf("%2c ", ' ');
    for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
        flag ? printf("%d ", p->pid) : printf("");
        printf("%s", status[p->status]);
        len = mx_strlen(status[p->status]);
        print_spaces(MAX_LEN + 1 - len);
        mx_print_args_in_line(p->argv, " ");
        (p->next != NULL) ? mx_printstr(" |\n       ") : mx_printstr("\n");
    }
}

void mx_print_pid_process_in_job(t_shell *m_s, int job_id) {
    t_process *p;

    if (job_id > MX_JOBS_NUMBER || m_s->jobs[job_id] == NULL) {
        mx_printstr("error job_id");
        mx_printstr("\n");
    }
    else {
        printf("[%d]", job_id);
        for (p = m_s->jobs[job_id]->first_pr; p != NULL; p = p->next) {
            printf(" %d", p->pid);
        }
        printf("\n");
    }
}

void mx_print_args_in_line(char **res, const char *delim) {
    if (!res || !delim)
        return;
    if (res[0] == NULL)
        mx_printstr("NULL\n");
    for (int i = 0; res[i] != NULL; i++) {
        mx_printstr(res[i]);
        if (res[i + 1] != NULL)
            mx_printstr(delim);
    }
}
