#include "ush.h"

void mx_group_shell(t_shell *shell) {
    pid_t shell_pgid;
    int terminal = STDIN_FILENO;

    if (!isatty(terminal)) {
        return;
    }

    for (; tcgetpgrp(terminal) != (shell_pgid = getpgrp());) {
        kill(-shell_pgid, SIGTTIN);
    }

    signal(SIGINT, MX_SIG_IGN);
    signal(SIGQUIT, MX_SIG_IGN);
    signal(SIGTSTP, MX_SIG_IGN);
    signal(SIGTTIN, MX_SIG_IGN);
    signal(SIGTTOU, MX_SIG_IGN);
    
    shell_pgid = getpid();

    if (setpgid(shell_pgid, shell_pgid) < 0) {
        perror("Couldn't put the shell in its own process group");

        exit(1);
    }

    tcsetpgrp(STDIN_FILENO, shell_pgid);
    shell->shell_pgid = shell_pgid;

    char *c_shell_pgid = mx_itoa(shell->shell_pgid);

    mx_set_variable(shell->variables, "$", c_shell_pgid);
    free(c_shell_pgid);
    
    tcgetattr(terminal, &shell->t_original);
    tcgetattr(terminal, &shell->tmodes);
}
