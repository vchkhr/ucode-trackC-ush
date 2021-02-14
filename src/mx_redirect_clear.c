#include "ush.h"

void mx_redirect_clear(t_redir **list) {
    if (!(*list) || !list) {
        return;
    }

    for (t_redir *queue = *list; queue;) {
        mx_strdel(&queue->input);
        mx_strdel(&queue->output);

        t_redir *temp = queue->next;
        free(queue);

        queue = temp;
    }

    *list = NULL;
}
