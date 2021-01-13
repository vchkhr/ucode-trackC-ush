#include "ush.h"

static int count_sep_first_lwl(t_ast *q) {
    int i = 1;

    for (; q; q = q->next)
        if (MX_IS_SEP_FIRST_LWL(q->type))
            i++;
    return i;
}

t_ast *push_redirections(t_ast **q, t_ast **ast) {
    int tmp_type;
    t_ast *c = (*q)->next;

    tmp_type = (*q)->type;
    for (; c && MX_IS_REDIRECTION(tmp_type); c = c->next, (*q) = (*q)->next) {
        mx_ast_push_back_redirection(ast, c->token, tmp_type);
        tmp_type = c->type;
    }
    for (c = *ast; c->next; c = c->next) {}
    c->type = tmp_type;
    return *q;
}

t_ast **mx_ast_parse(t_ast *parsed_line) {
    t_ast *q = parsed_line;
    int k = count_sep_first_lwl(q);
    t_ast **ast = (t_ast **)malloc((k + 1) * sizeof(t_ast *));
    int i = 0;

    ast[i] = NULL;
    for (; q; q = q->next) {
        mx_ast_push_back(&ast[i], q->token, q->type);
        if (MX_IS_REDIRECTION(q->type))
            q = push_redirections(&q, &ast[i]);
        if (MX_IS_SEP_FIRST_LWL(q->type) || q->type == NUL)
            ast[++i] = NULL;
    }
    return ast;
}
