#include "ush.h"

static void fill_options(int n_options, which_t *which_options, char **args) {
    for(int i = n_options; i > 0; i --) {
        for (int j = mx_strlen(args[i]); j > 0; j--) {
            if (args[i][j] == 'a') which_options->a = 1;
            if (args[i][j] == 's') which_options->s = 1;
        }
    }
}

int mx_which(t_shell *m_s, t_process *p) {
    which_t which_options = {0, 0};
    int n_options = mx_count_options(p->argv, "as",
                                     "which", " [-as] program ...");
    int flag = 0;
    int exit_code = 0;

    fill_options(n_options, &which_options, p->argv);
    if (n_options < 0)
        return 1;
    for (int i = n_options + 1; p->argv[i] != NULL; i++) {
        mx_get_command_info(m_s, p->argv[i], &flag, which_options);
        if (!flag)
            exit_code = 1;
    }
    return exit_code;
}
