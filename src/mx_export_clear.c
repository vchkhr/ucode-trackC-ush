#include "ush.h"

void mx_export_clear(t_export *list) {
    if (!(list) || !list) {
        return;
    }

    for (t_export *queue = list, *temp = NULL; queue; queue = temp) {
        if (queue->name) {
            free(queue->name);
        }
        if (queue->value) {
            free(queue->value);
        }

        temp = queue->next;
        free(queue);
    }
    
    list = NULL;
}
