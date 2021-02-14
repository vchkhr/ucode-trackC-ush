#include "ush.h"

void mx_append_redirect(t_ast **head, char *argument, int type) {
    if (!head || !argument) {
        return;
    }

    t_ast *process;

    process = *head;

    if (*head == NULL) {
        mx_printerr("u$h: trying to connect redirection to empry process.\n");

        return;
    }
    else {
        for (; process->next != NULL;) {
            process = process->next;
        }
        
        mx_append(&process->previous, argument, type);
    }
}
