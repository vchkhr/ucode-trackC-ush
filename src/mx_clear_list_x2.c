#include "ush.h"

void mx_clear_list_x2(t_ast **list) {
    if (!(*list) || !list) {
        return;
    }

    t_ast *queue = *list;

    for (t_ast *temp = NULL; queue; queue = temp) {
        if (queue->token) {
            free(queue->token);
        }
        if (queue->arguments) {
            mx_del_strarr(&queue->arguments);
        }
        if (queue->previous) {
            mx_clear_list_x2(&queue->previous);
        }

        temp = queue->next;
        free(queue);
    }
    
    *list = NULL;
}
