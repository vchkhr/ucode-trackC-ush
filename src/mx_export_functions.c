#include "ush.h"

static int check_identifier(char *arg) {
    int flag = 0;
    int name_len = mx_get_char_index(arg, '=');

    if (name_len == 0) {
        flag++;
    }
    for (int j = 0; j < name_len; j++) {
        if (!isalpha(arg[j]) && !isdigit(arg[j]) && arg[j] != '_') {
            flag++;
        }
    }
    return flag;
}

static void print_export_error(char *arg, int *exit_code) {
    mx_printerr("ush: export: `");
    mx_printerr(arg);
    mx_printerr("': not a valid identifier\n");
    *exit_code = 1;
}

static void export_value(t_export *export, char *name, char *value) {
    int flag = 0;
    t_export *head = export;

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            flag++;
            free(head->value);
            head->value = strdup(value);
            break;
        }
        head = head->next;
    }
    if (!flag) {
        mx_push_export(&export, name, value);
    }
}

static void get_data (char *arg, char **name, char **value,
                      t_export *variables) {
    int idx = mx_get_char_index(arg,'=');

    if (idx < 0)
        *name = strdup(arg);
    else {
        *name = strndup(arg,idx);
        *value = mx_strdup_from(arg,idx);
    }
    if (*value == NULL) {
        t_export *head = variables;

        while (head != NULL) {
            if (strcmp(head->name, *name) == 0) {
                *value = strdup(head->value);
                break;
            }
            head = head->next;
        }
    }
}

void mx_export_or_error(char *arg, t_export *export,
    t_export *variables, int *exit_code) {
    int flag = check_identifier(arg);

    if (flag)
        print_export_error(arg, exit_code);
    else {
        char *name = NULL;
        char *value = NULL;

        get_data(arg, &name, &value, variables);
        if (value != NULL)
            setenv(name, value, 1);
        export_value(export, name, value);
        export_value(variables, name, value);
        mx_clear_data(name, value);
        *exit_code = 0;
    }
}
