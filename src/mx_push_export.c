#include "ush.h"

void mx_export_push(t_export **list, void *name, void *value) {
    t_export *temp;
    t_export *process;

    if (!list) {
        return;
    }

    temp = mx_create_node_export(name, value);

    if (!temp) {
        return;
    }

    process = *list;

    if (*list == NULL) {
        *list = temp;

        return;
    }
    else {
        for (; process->next != NULL;) {
            process = process->next;
        }
        
        process->next = temp;
    }
}
