#include "ush.h"

static char *strdup_from(char *str, int index) {
    for (int i = 0; i <= index; i++) {
        str++;
    }
    return strdup(str);
}

static void get_data (char *arg, char **name, char **value) {
    int idx = mx_get_char_index(arg,'=');
 
    *name = strndup(arg,idx);
    *value = strdup_from(arg,idx);
}

void mx_export_value(t_export *export, char *name, char *value) {
    t_export *head = export;

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            if (head->value)
                free(head->value);
            head->value = strdup(value);
            setenv(name, value, 1);
            break;
        }
        head = head->next;
    }
}

int mx_set_parametr(char **args, t_shell *m_s) {
    char *name;
    char *value;

    for (int i = 0; args[i] != NULL; i++) {
        name = NULL;
        value = NULL;
        get_data(args[i], &name, &value);
        if (value != NULL && name != NULL) {
            mx_set_variable(m_s->variables, name, value);
            mx_export_value(m_s->exported, name, value);
        }
        if (name)
            free(name);
        if (value)
            free(value);
    }
    return 0;
}
