#include "ush.h"

void mx_ast_clear_list(t_ast **list) {
    t_ast *q = *list;
    t_ast *tmp = NULL;

    if (!(*list) || !list)
        return;
    while (q) {
        if (q->token)
            free(q->token);
        if (q->args)
            mx_del_strarr(&q->args);
        if (q->left)
            mx_ast_clear_list(&q->left);
        tmp = q->next;
        free(q);
        q = tmp;
    }
    *list = NULL;
}

void mx_ast_clear_all(t_ast ***list) {
    t_ast **q = *list;

    for (int i = 0; q[i]; i++)
        mx_ast_clear_list(&q[i]);
    free(q);
    q = NULL;
}
