#include "ush.h"

static void manage_env(char *dir, t_shell *m_s,  cd_t cd_options,
                       int *exit_code) {
    char *link = malloc(1024);

    readlink(dir, link, 1024);
    if (cd_options.P == 1 && strcmp(link, "") != 0) {
        free(dir);
        dir = getcwd(NULL, 1024);
    }
    free(link);
    setenv("OLDPWD", m_s->pwd, 1);
    mx_set_variable(m_s->variables, "OLDPWD", m_s->pwd);
    mx_set_variable(m_s->exported, "OLDPWD", m_s->pwd);
    setenv("PWD", dir, 1);
    mx_set_variable(m_s->variables, "PWD", dir);
    mx_set_variable(m_s->exported, "PWD", dir);
    free(m_s->pwd);
    m_s->pwd = strdup(dir);
    free(dir);
    (*exit_code) = 0;
}

static void print_error_cd(char *point) {
    mx_printerr("ush: cd: ");
    perror(point);
}

static int check_path(char *point, cd_t cd_options) {
    int flag = 0;
    char *read_link = realpath(point, NULL);

    if (cd_options.s) {
        if(read_link && strcmp(point, read_link) != 0) {
            mx_printerr("ush: cd: ");
            mx_printerr(point);
            mx_printerr(": Not a directory");
            mx_printerr("\n");
            flag++;
        }
    }
    free(read_link);
    return flag;
}

void mx_change_dir(char *point, cd_t cd_options, t_shell *m_s, int *exit_code){
    char *dir = mx_normalization(point, m_s->pwd);
    int flag = check_path(point, cd_options);

    if (!flag) {
        if (chdir(dir) != 0) {
            print_error_cd(point);
            free(dir);
        }
        else
            manage_env(dir, m_s, cd_options, exit_code);
    }
    else
        free(dir);
    free(m_s->git);
    if (getenv("HOME"))
        m_s->git = mx_get_git_info();
}
