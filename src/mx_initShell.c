#include "ush.h"

static char *get_pwd(void) {
    char *pwd = getenv("PWD");
    char *cur_dir = getcwd(NULL, 256);
    char *read_link = realpath(pwd, NULL);

    if (read_link && strcmp(cur_dir, read_link) == 0){
        pwd = strdup(getenv("PWD"));
        free(read_link);
        free(cur_dir);
    }
    else {
        pwd = strdup(cur_dir);
        free(cur_dir);
    }
    return pwd;
}

static void set_path(t_shell *m_s) {
    char *cur_dir = getcwd(NULL, 256);
    char *path = NULL;

    m_s->kernal = mx_strjoin(cur_dir, "/ush");
    if (!getenv("PATH")) {
        path = strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
        path = mx_strjoin_free(path, "/usr/local/munki");
    }
    else
        path = strdup(getenv("PATH"));
    setenv("PATH", path, 1);
    free(path);
    free(cur_dir);
}

static void set_shell_defaults(t_shell *m_s) {
    char *b_list[19] = {"env", "export", "unset", "echo", "jobs", "fg", "bg",
                        "cd", "pwd", "which", "exit", "set", "kill", "chdir",
                        "true", "alias", "declare", "false", NULL};
    m_s->builtin_list = (char **) malloc(sizeof(char *) * 19);

    for (int i = 0; i < 19; i++)
        m_s->builtin_list[i] = b_list[i];
    m_s->max_number_job = 1;
    m_s->exit_flag = 0;
    m_s->history_count = 0;
    m_s->history_size = 1000;
    m_s->history = (char **)malloc(sizeof(char *) * m_s->history_size);
    for (int i = -1; i < MX_JOBS_NUMBER; ++i)
        m_s->jobs[i] = NULL;
    m_s->functions = NULL;
    m_s->aliases = NULL;
    mx_init_jobs_stack(m_s);
    set_path(m_s);
}

t_shell *mx_init_shell(int argc, char **argv) {
    char *shlvl;
    t_shell *m_s = (t_shell *) malloc(sizeof(t_shell));

    set_shell_defaults(m_s);
    m_s->argc = argc;
    m_s->argv = argv;
    m_s->pwd = get_pwd();
    setenv("PWD", m_s->pwd, 1);
    setenv("OLDPWD", m_s->pwd, 1);
    shlvl = mx_get_shlvl();
    setenv("SHLVL", shlvl, 1);
    free(shlvl);
    m_s->exported = mx_set_export();
    m_s->variables = mx_set_variables();
    m_s->prompt = strdup("u$h");
    m_s->prompt_status = 1;
    mx_set_variable(m_s->variables, "PROMPT", "u$h");
    mx_set_shell_grp(m_s);
    m_s->exit_code = -1;
    return m_s;
}
