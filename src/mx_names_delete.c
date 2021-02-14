#include "ush.h"

void mx_names_delete(t_export **list, char *argument) {
    t_export *head = *list;

    if (head != NULL && strcmp(head->name, argument) == 0) {
        *list = (*list)->next;

        return;
    }

    for (; head != NULL; head = head->next) {
        if (head->next != NULL && strcmp(head->next->name, argument) == 0) {
            free(head->next->name);
            free(head->next->value);
            free(head->next);

            head->next = head->next->next;
            
            break;
        }
    }
}
