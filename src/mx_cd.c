#include "ush.h"

static char *replace_sub(char *str, char *sub, char *replace) {
    char *result;
    int index = mx_get_substr_index(str,sub);
    char *buff_1 = strndup(str, index);
    char *buff_2;
    char *tmp = NULL;

    for (int i = 0; i < index + mx_strlen(sub); i++) {
        str++;
    }
    buff_2 = strdup(str);
    result = mx_strjoin(buff_1, replace);
    tmp = mx_strjoin(result,buff_2);
    free(result);
    result = strdup(tmp);
    free(tmp);
    free(buff_1);
    free(buff_2);
    return(result);
}

static char *chpwd(char **args, int n_options, t_shell *m_s) {
    char *current = strdup(m_s->pwd);
    char *new = NULL;

    if (!mx_strstr(current, args[n_options + 1])) {
        mx_printerr("ush: cd: string not in pwd: ");
        mx_printerr(args[n_options + 1]);
        mx_printerr("\n");
    }
    else {
        new = replace_sub(current, args[n_options + 1], args[n_options + 2]);
    }
    free(current);
    return new;
}

static void fill_options(int n_options, cd_t *cd_options, char **args) {
    for(int i = n_options; i > 0; i --) {
        for (int j = mx_strlen(args[i]); j > 0; j--) {
            if (args[i][j] == 'L' && cd_options->P <= 0) cd_options->L = 1;
            if (args[i][j] == 'P' && cd_options->L <= 0) cd_options->P = 1;
            if (args[i][j] == 's') cd_options->s = 1;
        }
    }
}

static int count_args(char **args, int n_options) {
    int n_args = 0;

    for (int i = n_options + 1; args[i] != NULL; i++) {
        n_args++;
    }
    if (n_args > 2)
        mx_printerr("ush: cd: too many arguments\n");
    return n_args;
}

int mx_cd(t_shell *m_s, t_process *p) {
    cd_t cd_options = {0, 0, 0};
    int n_options = mx_count_options(p->argv, "sLP", "cd",
                                     " [-s] [-L|-P] [dir]");
    int n_args = count_args(p->argv, n_options);
    char *point = NULL;
    int exit_code = 1;


    fill_options(n_options, &cd_options, p->argv);
    if (n_options >= 0 && n_args < 3) {
        if (n_args == 0)
            point = mx_go_home();
        else if (n_args == 2)
            point = chpwd(p->argv, n_options, m_s);
        else
            point = mx_go_somewere(p, n_options);
        if (point)
            mx_change_dir(point, cd_options, m_s, &exit_code);
        free(point);
    }
    return exit_code;
}
