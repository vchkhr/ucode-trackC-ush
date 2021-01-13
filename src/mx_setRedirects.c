#include "ush.h"

static int set_flag(int redir_delim) {
    int flags = 0;

    if (redir_delim == R_OUTPUT)
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    if (redir_delim == R_OUTPUT_DBL)
        flags = O_WRONLY | O_CREAT;
    return flags;
}

int mx_set_redirections(t_shell *m_s, t_job *job, t_process *p) {
    mx_count_redir(p);
    m_s->redir = 0;

    mx_set_r_infile(m_s, job, p);
    mx_set_r_outfile(m_s, job, p);
    p->errfile = job->errfile;

    if (m_s->redir == 1) {
        m_s->exit_code = 1;
        job->exit_code = 1;
        mx_set_variable(m_s->variables, "?", "1");
    }
    return m_s->redir;
}

void mx_count_redir(t_process *p) {
    t_redir *r;

    p->c_input = 0;
    p->c_output = 0;
    for (r = p->redirect; r; r = r->next) {
        if (r->redir_delim == R_INPUT || r->redir_delim == R_INPUT_DBL)
            p->c_input += 1;
        if (r->redir_delim == R_OUTPUT || r->redir_delim == R_OUTPUT_DBL)
            p->c_output += 1;
    }
    if (p->c_input == 0)
        p->c_input++;
    if (p->c_output == 0)
        p->c_output++;
    p->r_outfile = (int *) realloc(p->r_outfile, sizeof(int) * (p->c_output));
}

void mx_set_r_outfile(t_shell *m_s, t_job *job, t_process *p) {
    int flags = 0;
    t_redir *r;
    int j = 0;
    int fd;

    p->r_outfile[0] = job->outfile;
    if (p->redirect) {
        for (r = p->redirect; r; r = r->next) {
            if (r->output_path) {
                 flags = set_flag(r->redir_delim);
                if ((fd = open(r->output_path, flags, 0666)) < 0) {
                    mx_printerr("ush :");
                    perror(r->output_path);
                    m_s->redir = 1;
                    continue;
                }
                p->r_outfile[j] = fd;
                lseek(p->r_outfile[j], 0, SEEK_END);
                j++;
            }
        }
    }
    job->outfile = p->r_outfile[0];
}
