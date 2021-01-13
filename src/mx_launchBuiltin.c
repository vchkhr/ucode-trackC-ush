#include "ush.h"

static void buildin_fork(t_shell *m_s, int job_id, int (*builtin_functions[])
                         (t_shell *m_s, t_process *p), t_process *p) {
    pid_t child_pid = fork();

    p->pid = child_pid;
    if (child_pid < 0) {
        perror("error fork");
        exit(1);
    }
    else if (child_pid == 0) {
        if (isatty(STDIN_FILENO))
            mx_pgid(m_s, job_id, child_pid);
        mx_dup_fd(p);
        p->exit_code = builtin_functions[p->type](m_s, p);
        exit(p->exit_code);
    }
    else {
        if (isatty(STDIN_FILENO)) {
            if (m_s->jobs[job_id]->pgid == 0)
                m_s->jobs[job_id]->pgid = child_pid;
            setpgid (child_pid, m_s->jobs[job_id]->pgid);
        }
    }
}

static void buildin_std_exec(t_shell *m_s, int (*builtin_functions[])
                             (t_shell *m_s, t_process *p), t_process *p) {
    int defoult;

    if (p->output_path) {
        defoult = dup(1);
        if (p->outfile != STDOUT_FILENO) {
            lseek(p->outfile, 0, SEEK_END);
            dup2(p->outfile, STDOUT_FILENO);
            close(p->outfile);
        }
        mx_dup_close(p->infile, STDIN_FILENO);
    }
    p->exit_code = builtin_functions[p->type](m_s, p);
    p->status = MX_STATUS_DONE;
    if (p->output_path) {
        if (p->outfile != STDOUT_FILENO) {
            dup2(defoult, 1);
            close(defoult);
        }
    }
}

int mx_launch_builtin(t_shell *m_s, t_process *p, int job_id) {
    int (*builtin_functions[])(t_shell *m_s, t_process *p) =
         {&mx_env, &mx_export, &mx_unset, &mx_echo, &mx_jobs, &mx_fg,
          &mx_bg, &mx_cd, &mx_pwd, &mx_which, &mx_exit, &mx_set,
          &mx_kill, &mx_chdir, &mx_true, &mx_alias, &mx_declare, 
          &mx_false, NULL};

    p->status = MX_STATUS_RUNNING;
    if (p->pipe || !p->foregrd) {  // If pipe or in foregrd -> fork
        buildin_fork(m_s, job_id, builtin_functions, p);
    }
    else
        buildin_std_exec(m_s, builtin_functions, p);
    return p->exit_code;
}

void mx_pgid(t_shell *m_s, int job_id, int child_pid) {
    if (m_s->jobs[job_id]->pgid == 0)
        m_s->jobs[job_id]->pgid = child_pid;
    setpgid(child_pid, m_s->jobs[job_id]->pgid);
    if (m_s->jobs[job_id]->foregrd)
        tcsetpgrp(STDIN_FILENO, m_s->jobs[job_id]->pgid);
    signal(SIGINT, MX_SIG_DFL);
    signal(SIGQUIT, MX_SIG_DFL);
    signal(SIGTSTP, MX_SIG_DFL);
    signal(SIGTTIN, MX_SIG_DFL);
    signal(SIGTTOU, MX_SIG_DFL);
    signal(SIGPIPE, mx_sig_h);
}

void mx_dup_close(int inp, int out) {
    if (inp != out) {
        dup2(inp, out);
        close(inp);
    }
}
