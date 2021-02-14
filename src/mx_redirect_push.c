#include "ush.h"

t_ast *mx_redirect_push(t_ast **queue, t_ast **ast) {
    t_ast *temp = (*queue)->next;
    int tmp_type = (*queue)->type;

    for (; temp && (tmp_type == 5 || tmp_type == 6 || tmp_type == 7 || tmp_type == 8); temp = temp->next, (*queue) = (*queue)->next) {
        mx_append_redirect(ast, temp->token, tmp_type);
        tmp_type = temp->type;
    }

    for (temp = *ast; temp->next;) {
        temp = temp->next;
    }

    temp->type = tmp_type;
    
    return *queue;
}
