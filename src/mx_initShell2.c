#include "ush.h"

static void shell_grp_help(t_shell *m_s, pid_t shell_pgid) {
    shell_pgid = getpid();
    if (setpgid(shell_pgid, shell_pgid) < 0) {
        perror("Couldn't put the shell in its own process group");
        exit(1);
    }
    tcsetpgrp(STDIN_FILENO, shell_pgid);  // Grab control of the terminal
    m_s->shell_pgid = shell_pgid;
}

void mx_set_shell_grp(t_shell *m_s) {
    pid_t shell_pgid;
    int shell_terminal = STDIN_FILENO;
    int shell_is_interactive = isatty(shell_terminal);

    if (shell_is_interactive) {
        while (tcgetpgrp(shell_terminal) != (shell_pgid = getpgrp()))
            kill(-shell_pgid, SIGTTIN);
        signal(SIGINT, MX_SIG_IGN);
        signal(SIGQUIT, MX_SIG_IGN);
        signal(SIGTSTP, MX_SIG_IGN);
        signal(SIGTTIN, MX_SIG_IGN);
        signal(SIGTTOU, MX_SIG_IGN);
        shell_grp_help(m_s, shell_pgid);
        char *c_shell_pgid = mx_itoa(m_s->shell_pgid);
        mx_set_variable(m_s->variables, "$", c_shell_pgid);
        free(c_shell_pgid);
        tcgetattr(shell_terminal, &m_s->t_original);
        tcgetattr(shell_terminal, &m_s->tmodes);
    }
}
