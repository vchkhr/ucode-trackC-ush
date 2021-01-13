#include "ush.h"

static int count_variables(char **args, int n_options) {
    int n_variables = 0;

    for (int i = n_options + 1; args[i] != NULL; i++) {
        if (mx_get_char_index(args[i],'=') < 0)
            break;
        if (mx_get_char_index(args[i],'=') == 0) {
            mx_printerr("env: setenv ");
            mx_printerr(args[i]);
            mx_printerr(": Invalid argument\n");
            return -1;
        }
        n_variables++;
    }
    return n_variables;
}

static int count_args(char **args, int n_all) {
    int n_args = 0;

    for (int i = n_all + 1; args[i] != NULL; i++) {
        n_args++;
    }
    return n_args;
}

static void print_env(t_export *env_list) {
    t_export *head = env_list;

    while (head != NULL) {
        printf("%s=%s\n", head->name, head->value);
        head = head->next;
    }
}

static t_env_builtin *init_env (t_process *p) {
    t_env_builtin *env = (t_env_builtin *)malloc(sizeof(t_env_builtin));

    env->env_params = NULL;
    env->env_list = NULL;
    env->env_options.i = 0;
    env->env_options.u = 0;
    env->env_options.P = 0;
    env->n_options = mx_count_env_options(p->argv, env);
    env->n_variables = count_variables(p->argv, env->n_options);
    env->n_args = count_args(p->argv, env->n_variables + env->n_options);
    env->path = NULL;
    return env;
}

int mx_env(t_shell *m_s, t_process *p) {
    t_env_builtin *env = init_env(p);
    int exit_code = 0;

    mx_set_data(env, p->argv);
    if (env->n_options < 0 || env->n_variables < 0) 
        exit_code = 1;
    else if (env->n_args == 0)
        print_env(env->env_list); 
    else
        mx_launch_command(p, env, &exit_code);
    if (env->path)
        free (env->path);
    m_s->exit_flag = 0;
    mx_clear_export(env->env_list);
    mx_clear_export(env->env_params);
    free(env);
    return exit_code;
}
