#include "ush.h"

static void fill_options(int n_options, pwd_t *pwd_options, char ** args) {
    int L_index = -1;
    int P_index = -1;

    for(int i = n_options; i > 0; i --) {
        for (int j = mx_strlen(args[i]); j > 0; j--) {
            if (args[i][j] == 'L' && P_index < 0) {
                L_index = 1;
            }
            if (args[i][j] == 'P' && L_index < 0) {
                P_index = 1;
            }
        }
    }
    pwd_options->L = L_index;
    pwd_options->P = P_index;
}

static int count_args(char **args, int n_options) {
    int n_args = 0;

    for (int i = n_options; args[i] != NULL; i++) {
        n_args++;
    }
    if (n_args > 1 && n_options >= 0)
        mx_printerr("ush: pwd: too many arguments\n");
    return n_args;
}

static void print_pwd(char *dir, int *exit_code,
                      t_shell *m_s, pwd_t pwd_options) {
    *exit_code = 0;
    if (pwd_options.P < 0)
        printf("%s\n", m_s->pwd);
    else
        printf("%s\n", dir);
    free(dir);
}

int mx_pwd(t_shell *m_s, t_process *p) {
    char *dir;
    pwd_t pwd_options = {0, 0};
    int n_options = mx_count_options(p->argv, "LP", "pwd", " [-LP]");
    int n_args = count_args(p->argv, n_options);
    int exit_code = 1;

    fill_options(n_options, &pwd_options, p->argv);
    if (n_options <  0 || n_args > 1)
        return 1;
    dir = getcwd(NULL, 1024);
    if (dir != NULL) {
        print_pwd(dir, &exit_code, m_s, pwd_options);
    }
    else
        perror("ush: pwd");
    return exit_code;
}
