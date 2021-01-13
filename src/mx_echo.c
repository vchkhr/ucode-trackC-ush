#include "ush.h"

static int count_options(char **args) {
    int n_options = 0;

    for (int i = 1; args[i] != NULL; i++) {
        if (args[i][0] == '-' ) {
            if (!strchr("neE",args[i][1]))
                break;
        }
        else
            break;
        n_options++;
    }
    return n_options;
}

static void fill_options(char **args, echo_t *echo_options, int n_options) {
    for (int i = n_options; i >= 0; i--) {
        for (int j = mx_strlen(args[i]); j >= 1; j--) {
            if (args[i][j] == 'n') {
                echo_options->n = 1;
            }
            else if (args[i][j] == 'e') {
                if (!echo_options->E)
                    echo_options->e = 1;
            }
            else if (args[i][j] == 'E') {
                if (!echo_options->e)
                    echo_options->E = 1;
            }
        }
    }
}

static void edit_argv(int n_options, t_process *p) {
    echo_t echo_options = {0, 0, 0};

    fill_options(p->argv, &echo_options, n_options);
    for(int i = n_options + 1; p->argv[i] != NULL; i++) {
        if (!echo_options.E && strstr(p->argv[i], "\\")) {
            mx_escape_seq(p, i, echo_options);
        }
        printf("%s",p->argv[i]);
        if (strstr(p->argv[i],"\\c"))
            break;
        if (p->argv[i + 1])
            mx_printstr(" ");
    }
    !echo_options.n ? printf("\n") : 0;
}

int mx_echo(t_shell *m_s, t_process *p) {
    m_s->exit_code = 0;
    int exit_code = m_s->exit_code;
    int n_options = count_options(p->argv);

    edit_argv(n_options, p);
    return exit_code;
}
