#include "ush.h"

static void get_data(int i, char **args, t_env_builtin *env) {
    int idx = mx_get_char_index(args[i],'=');
    char *name = strndup(args[i],idx);
    char *value = mx_strdup_from(args[i],idx);

    mx_push_export(&env->env_list, name, value);
    free(name);
    free(value);
}

static void delete_name(t_export **list, char *arg) {
    t_export *head = *list;

    if (head != NULL && strcmp(head->name, arg) == 0) {
        *list = (*list)->next;
        return;
    }
    while (head != NULL) {
        if (head->next != NULL) {
            if (strcmp(head->next->name, arg) == 0) {
                free(head->next->name);
                free(head->next->value);
                free(head->next);
                head->next = head->next->next;
                break;
            }
        }
        head = head->next;
    }
}

static void get_params (t_export *env_params, t_export *env_list,
                        t_env_builtin *env) {
    t_export *head = env_params;

    while (head != NULL) {
        if (strcmp(head->name, "u") == 0) {
            delete_name(&env_list, head->value);
        }
        if (strcmp(head->name, "P") == 0) {
            if (env->path != NULL)
                free(env->path);
            env->path = strdup(head->value);
        }
        head = head->next;
    }
}

void mx_set_data(t_env_builtin *env, char *args[]) {
    extern char** environ;

    for (int i = 0; environ[i] != NULL; i++) {
        if (!env->env_options.i) {
            get_data(i, environ, env);
        }
    }
    get_params(env->env_params, env->env_list, env);
    for (int i = env->n_options + 1;
         i <= env->n_options + env->n_variables; i++) {
        get_data(i, args, env);
    }
}
