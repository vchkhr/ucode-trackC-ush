#include "ush.h"

static void execute_job_env (t_job *job) {
    extern char **environ;

    job->env = environ;
    job->path = getenv("PATH");
    if (!job->path)
        job->path = "";
}

static void help_ex_job (t_shell *m_s, t_job *job, t_process *p, int job_id) {
    p->infile = job->infile;
    p->outfile = job->outfile;
    p->errfile = job->errfile;
    job->flag = 0;
    if (!p->pipe)
        job->flag = mx_get_flag(p->argv);
    if (job->flag) {
        job->exit_code = mx_set_parametr(p->argv, m_s);
        mx_remove_job(m_s, job_id);
    }
    else if (p->type != -1)
        job->exit_code = mx_launch_builtin(m_s, p, job_id);
    else
        job->exit_code = mx_launch_process(m_s, p, job_id);
    if (job->infile != job->stdin)
        close(job->infile);
    if (job->outfile != job->stdout)
        close(job->outfile);
    m_s->exit_code = job->exit_code;
}

static void launch_help (t_shell *m_s, t_job *job, int job_id, int status) {
    int shell_terminal = STDIN_FILENO;

    if (job->foregrd) {
        tcsetpgrp(STDIN_FILENO, job->pgid);
        if (status > 0) {
            status = mx_wait_job(m_s, job_id);
        }
        else if (status == 0) {
            status = mx_wait_job(m_s, job_id);
            m_s->exit_code = status;
        }
        if (mx_job_completed(m_s, job_id))
            mx_remove_job(m_s, job_id);
        signal(SIGTTOU, MX_SIG_IGN);
        tcsetpgrp(STDIN_FILENO, getpid());
        tcgetattr(shell_terminal, &job->tmodes);
        tcsetattr(shell_terminal, TCSADRAIN, &m_s->tmodes);
    }
    else{
        mx_print_pid_process_in_job(m_s, job->job_id);
    }
}

static void m_pipe(t_shell *m_s, t_job * job, int mypipe[2], int job_id) {
    if (pipe(mypipe) < 0) {
        perror("pipe");
        mx_remove_job(m_s, job_id);
        exit(1);
    }
    job->outfile = mypipe[1];
}

static int execute_job (t_shell *m_s, t_job * job, int job_id) {
    t_process *p;
    int mypipe[2];

    execute_job_env(job);
    for (p = m_s->jobs[job_id]->first_pr; p; p = p->next) {
        mx_sheck_exit(m_s, p);
        if ((mx_set_redirections(m_s, job, p)) != 0) {
            p->status = MX_STATUS_DONE;
            p->exit_code = 1;
            continue;
        }
        if (p->pipe){
            m_pipe(m_s, job, mypipe, job_id);
            p->r_outfile[0] = job->outfile;
        }
        help_ex_job(m_s, job, p, job_id);
        job->infile = mypipe[0];
    }
    launch_help(m_s, job, job_id, job->exit_code);
    return job->exit_code;
}

void mx_launch_job (t_shell *m_s, t_job *job) {
    setbuf(stdout, NULL);
    int status = 0;
    int job_id;

    mx_check_jobs(m_s);
    job_id = mx_insert_job(m_s, job);
    if (!job->job_type)
        status = execute_job(m_s, job, job_id);
    else if (job->job_type == AND && m_s->exit_code == 0)
        status = execute_job(m_s, job, job_id);
    else if (job->job_type == OR && m_s->exit_code != 0)
        status = execute_job(m_s, job, job_id);
    else
        mx_remove_job(m_s, job_id);
    !m_s->exit_code ? m_s->exit_code = status : 0;
    char *exit_status = mx_itoa(m_s->exit_code);
    mx_set_variable(m_s->variables, "?", exit_status);
    free(exit_status);
}
