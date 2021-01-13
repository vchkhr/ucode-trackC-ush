#include "ush.h"

int mx_builtin_commands_idex(t_shell *m_s, char *command) {
    int i = 0;

    for (i = 0; m_s->builtin_list[i] != NULL; i++) {
        if (strcmp(command, m_s->builtin_list[i]) == 0)
            return (i);
    }
    return (-1);
}

int mx_get_flag(char **args) {
    int flag = 1;

    for (int i = 0; args[i] != NULL; i++) {
        if (mx_get_char_index(args[i],'=') <= 0) {
            flag--;
            break;
        }
    }
    return flag;
}

void mx_sheck_exit(t_shell *m_s, t_process *p) {
    mx_set_variable(m_s->variables, "_", p->argv[0]);
    setenv("_", p->argv[0], 1);
    if (m_s->exit_flag == 1 && !(p->type == 10))
        m_s->exit_flag = 0;
}

void mx_print_error(char *command, char *error) {
    mx_printerr("ush: ");
    if (error) {
        mx_printerr(command);
        mx_printerr(error);
    }
    else
        perror(command);
}

char *mx_get_shlvl(void) {
    char *shlvl = NULL;
    int lvl;

    shlvl = getenv("SHLVL");
    if (!shlvl)
        shlvl = "0";
    lvl = atoi(shlvl);
    lvl++;
    shlvl = mx_itoa(lvl);
    return shlvl;
}
