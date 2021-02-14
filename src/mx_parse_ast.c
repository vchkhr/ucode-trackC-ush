#include "ush.h"

t_ast **mx_parse_ast(t_ast *string) {
    t_ast *queue = string;
    t_ast **ast = (t_ast **)malloc((mx_first_level(queue) + 1) * sizeof(t_ast *));

    ast[0] = NULL;

    for (int i = 0; queue; queue = queue->next) {
        mx_append(&ast[i], queue->token, queue->type);

        if (queue->type == 5 || queue->type == 6 || queue->type == 7 || queue->type == 8) {
            queue = mx_redirect_push(&queue, &ast[i]);
        }
        if ((queue->type == 0 || queue->type == 1 || queue->type == 2 || queue->type == 3) || queue->type == 9) {
            ast[++i] = NULL;
        }
    }
    
    return ast;
}
