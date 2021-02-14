#include "ush.h"

void mx_set_variable(t_export *export, char *name, char *value) {
    int flag = 0;

    for (t_export *head = export; head != NULL; head = head->next) {
        if (strcmp(head->name, name) == 0) {
            free(head->value);
            head->value = strdup(value);
            flag++;

            break;
        }
    }

    if (!flag) {
        mx_export_push(&export, name, value);
    } 
}
