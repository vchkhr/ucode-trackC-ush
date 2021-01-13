#include "ush.h"

static int count_args(char **args, int n_options) {
    int n_args = 0;

    for (int i = n_options; args[i] != NULL; i++) {
        n_args++;
    }
    return n_args;
}

static int check_identifier(char *arg) {
    int flag = 0;

    for (int j = 0; j < mx_strlen(arg); j++) {
        if (!isalpha(arg[j]) && !isdigit(arg[j]) && arg[j] != '_') {
            flag++;
        }
    }
    return flag;
}

static void delete_name(t_export **list, char *arg) {
    t_export *head = *list;

    if (strcmp(head->name, arg) == 0) {
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

static void unset_or_error(t_shell *m_s, char *arg, int *exit_code) {
    int flag = check_identifier(arg);

    if (flag) {
        mx_printerr("ush: unset: `");
        mx_printerr(arg);
        mx_printerr("': not a valid identifier\n");
    }
    else {
        delete_name(&m_s->exported, arg);
        delete_name(&m_s->variables, arg);
        unsetenv(arg);
        exit_code = 0;
    }
}

int mx_unset(t_shell *m_s, t_process *p) {
    int n_options = mx_count_options(p->argv, "", "unset", " [name ...] ");
    int n_args = count_args(p->argv, n_options);
    int i = 0;
    int exit_code = 0;

    if (n_options <  0 || n_args == 1) {
        // if (n_args == 1)
        //     mx_printerr("unset: not enough arguments\n");
        return 1;
    }
    else {
        i = n_options + 1;
        while (p->argv[i] != NULL) {
            unset_or_error(m_s, p->argv[i], &exit_code);
            i++;
        }
    }
    return exit_code;
}
