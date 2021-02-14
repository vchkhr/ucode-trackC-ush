#include "ush.h"

void mx_process_append(t_process **process, t_shell *shell, t_ast *list) {
    t_process *queue;

    if (!process || !shell || !list) {
        return;
    }

    t_process *temp = mx_process_create(shell, list);

    if (!temp) {
        return;
    }

    queue = *process;

    if (*process == NULL) {
        *process = temp;

        return;
    }
    else {
        for (; queue->next != NULL;) {
            queue = queue->next;
        }

        queue->next = temp;
    }
}
