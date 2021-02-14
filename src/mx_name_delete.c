#include "ush.h"

void mx_name_delete(t_export **list, char *argument) {
    t_export *head = *list;

    if (strcmp(head->name, argument) == 0) {
        *list = (*list)->next;

        return;
    }

    for (; head != NULL; head = head->next) {
        if (head->next != NULL) {
            if (strcmp(head->next->name, argument) == 0) {
                free(head->next->name);
                free(head->next->value);
                free(head->next);

                head->next = head->next->next;
                
                break;
            }
        }
    }
}
