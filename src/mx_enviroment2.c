#include "ush.h"

static char **get_args(t_process *p, int start) {
    char **args_arr = (char **)malloc(sizeof(char *) * 256);
    int i = start;

    while (p->argv[i] != NULL) {
        args_arr[i - start] = strdup(p->argv[i]);
        i++;
    }
    mx_del_strarr(&p->argv);
    args_arr[i - start] = NULL;
    return args_arr;
}

static char **get_env_arr(t_export *env_list) {
    char **env_arr = (char **)malloc(sizeof(char *) * 1024);
    t_export *head = env_list;
    int i = 0;
    char *str;
    char *tmp;

    while (head != NULL) {
        str = NULL;
        tmp = mx_strjoin(head->name, "=");
        str = mx_strjoin(tmp, head->value);
        free(tmp);
        env_arr[i] = strdup(str);
        free(str);
        i++;
        head = head->next;
    }
    env_arr[i] = NULL;
    return env_arr;
}

void mx_launch_command( t_process *p, t_env_builtin *env, int *exit_code) {
    char **args_arr = get_args(p, env->n_options + env->n_variables + 1);
    char **env_arr = get_env_arr(env->env_list);

    if (!env->path)
        env->path = strdup(getenv("PATH"));
    p->argv = args_arr;
    *exit_code = mx_launch_bin(p, env->path, env_arr);
    mx_del_strarr(&env_arr);
}
