#include "ush.h"

static t_ast *ast_create_node(char *arg, int type) {
    t_ast *q;

    if (!arg)
        return NULL;
    q = (t_ast *)malloc(sizeof(t_ast));
    if (!q)
        return NULL;
    q->args = NULL;
    q->token = strdup(arg);
    q->type = type;
    q->next = NULL;
    q->left = NULL;
    return q;
}

void mx_ast_push_back(t_ast **head, char *arg, int type) {
    t_ast *q;
    t_ast *p;

    if (!head || !arg)
        return;
    q = ast_create_node(arg, type);
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

void mx_ast_push_back_redirection(t_ast **head, char *arg, int type) {
    t_ast *p;

    if (!head || !arg)
        return;
    p = *head;
    if (*head == NULL) {
        mx_printerr("u$h: trying to connect redirection to empry process.\n");
        return;
    }
    else {
        while (p->next != NULL)
            p = p->next;
        mx_ast_push_back(&p->left, arg, type);
    }
}
