#include "ush.h"

static void get_data(char *arg, char **name, char **value) {
    int idx = mx_get_char_index(arg, '=');
    int len = 0;

    *name = mx_strndup(arg, idx);
    if (arg[idx + 1] == '\"') {
        len = mx_strlen(&arg[idx + 2]);
        *value = mx_strndup(&arg[idx + 2], len - 1);
    }
}
/*
 * Get aliases if any.
 */
void mx_get_aliases(char *line, t_shell *m_s) {
    char **args = mx_parce_tokens(line);

    for (int i = 0; args[i]; i++) {
        char *name = NULL;
        char *value = NULL;

        get_data(args[i], &name, &value);
        if (value && name && mx_strcmp(value, name)) {
            if (m_s->aliases)
                mx_set_variable(m_s->aliases, name, value);
            else
                mx_push_export(&m_s->aliases, name, value);
        }
        mx_strdel(&name);
        mx_strdel(&value);
    }
    free(args);
}
