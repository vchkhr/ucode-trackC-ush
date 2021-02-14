#include "ush.h"

t_ast *mx_node_create(char *argument, int type) {
    if (!argument) {
        return NULL;
    }

    t_ast *queue;

    queue = (t_ast *)malloc(sizeof(t_ast));

    if (!queue) {
        return NULL;
    }

    queue->arguments = NULL;
    queue->token = strdup(argument);
    queue->type = type;
    queue->next = NULL;
    queue->previous = NULL;
    
    return queue;
}
