#include "ush.h"

void mx_redirect_append(t_redir **head, char *path, int type) {
    if (!head || !path) {
        return;
    }

    t_redir *queue = mx_redirect_create_node(path, type);

    if (!queue) {
        return;
    }

    t_redir *process = *head;

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
