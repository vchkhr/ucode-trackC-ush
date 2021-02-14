#include "ush.h"

t_redir *mx_redirect_create_node(char *path, int type) {
    if (!path) {
        return NULL;
    }

    t_redir *queue = (t_redir *)malloc(sizeof(t_redir));

    if (!queue) {
        return NULL;
    }

    queue->input = NULL;
    queue->output = NULL;

    if (type == 5 || type == 6) {
        queue->input = mx_strdup(path);
    }
    else if (type == 7 || type == 8) {
        queue->output = mx_strdup(path);
    }
    else {
        return NULL;
    }

    queue->delimiter = type;
    queue->next = NULL;
    
    return (queue);
}
