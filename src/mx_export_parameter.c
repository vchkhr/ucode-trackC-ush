#include "ush.h"

void mx_export_parameter(t_export *export, char *name, char *value) {
    for (t_export *head = export; head != NULL; head = head->next) {
        if (strcmp(head->name, name) == 0) {
            if (head->value) {
                free(head->value);
            }

            head->value = strdup(value);
            setenv(name, value, 1);
            
            break;
        }
    }
}
