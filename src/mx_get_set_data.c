#include "ush.h"

void mx_get_set_data(int i, char **arguments, t_default *environment) {
    int index = mx_get_char_index(arguments[i], '=');
    char *name = strndup(arguments[i], index);
    char *value = mx_strdup_index(arguments[i], index);

    mx_export_push(&environment->list, name, value);
    
    free(name);
    free(value);
}
