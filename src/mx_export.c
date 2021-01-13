#include "ush.h"

static int count_args(char **args, int n_options) {
    int n_args = 0;

    for (int i = n_options; args[i] != NULL; i++) {
        n_args++;
    }
    return n_args;
}

static void print_export(t_export *export) {
    t_export *head = export;

    while (head != NULL) {
        if (strncmp(head->name,"BASH_FUNC_",10) != 0) {
            printf("export %s", head->name);
            if (head->value)
                printf("=\"%s\"", head->value);
            printf("\n");
        }
        head = head->next;
    }
}

void mx_clear_data(char *name, char *value) {
    if(name)
        free(name);
    if(value)
        free(value);
}

int mx_export(t_shell *m_s, t_process *p) {
    int n_options = mx_count_options(p->argv, "p", "export",
     " [name[=value] ...] or export -p");
    int n_args = count_args(p->argv, n_options);
    int i = 0;
    int exit_code = 0;

    if (n_options <  0)
        return 1;
    if (n_args == 1)
        print_export(m_s->exported);
    else {
        i = n_options + 1;
        while (p->argv[i] != NULL) {
            mx_export_or_error(p->argv[i], m_s->exported,
                               m_s->variables, &exit_code);
            i++;
        }
    }
    return exit_code;
}
