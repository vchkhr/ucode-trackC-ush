#include "ush.h"

static t_redir *redir_create_node(char *path, int type) {
    t_redir *q;

    if (!path)
        return NULL;
    q = (t_redir *)malloc(sizeof(t_redir));
    if (!q)
        return NULL;
    q->input_path = NULL;
    q->output_path = NULL;
    if (MX_IS_REDIR_INP(type))
        q->input_path = mx_strdup(path);
    else if (MX_IS_REDIR_OUTP(type))
        q->output_path = mx_strdup(path);
    else
        return NULL;
    q->redir_delim = type;
    q->next = NULL;
    return (q);
}

void mx_redir_push_back(t_redir **head, char *path, int type) {
    t_redir *q;
    t_redir *p;

    if (!head || !path)
        return;
    q = redir_create_node(path, type);
    if (!q)
        return;
    p = *head;
    if (*head == NULL) {
        *head = q;
        return;
    }
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = q;
    }
}

void mx_redir_clear_list(t_redir **list) {
    t_redir *q = *list;
    t_redir *tmp = NULL;

    if (!(*list) || !list)
        return;
    while (q) {
        mx_strdel(&q->input_path);
        mx_strdel(&q->output_path);
        tmp = q->next;
        free(q);
        q = tmp;
    }
    *list = NULL;
}
