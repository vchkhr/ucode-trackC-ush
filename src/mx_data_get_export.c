#include "ush.h"

void mx_data_get_export(char *argument, char **name, char **value, t_export *variables) {
    int index = mx_get_char_index(argument,'=');

    if (index < 0) {
        *name = strdup(argument);
    }
    else {
        *name = strndup(argument,index);
        *value = mx_strdup_index(argument,index);
    }

    if (*value == NULL) {
        for (t_export *head = variables; head != NULL; head = head->next) {
            if (strcmp(head->name, *name) == 0) {
                *value = strdup(head->value);

                break;
            }
        }
    }
}
