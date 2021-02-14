#include "ush.h"

void mx_value_export(t_export *export, char *name, char *value) {
    int flag = 0;

    for (t_export *head = export; head != NULL;) {
        if (strcmp(head->name, name) == 0) {
            flag++;

            head->value = strdup(value);

            free(head->value);

            break;
        }

        head = head->next;
    }
    
    if (!flag) {
        mx_export_push(&export, name, value);
    }
}
