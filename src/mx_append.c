#include "ush.h"

void mx_append(t_ast **head, char *argument, int type) {
    if (!head || !argument) {
        return;
    }

    t_ast *queue;

    queue = mx_node_create(argument, type);

    if (!queue) {
        return;
    }

    t_ast *process;

    process = *head;

    if (*head == NULL) {
        *head = queue;

        return;
    }
    else {
        for (; process->next != NULL;) {
            process = process->next;
        }

        process->next = queue;
    }
}
