#include "ush.h"

t_ast **mx_create_ast(char *string, t_shell *shell) {
    t_ast **ast = NULL;
    t_ast *parse = NULL;

    if (!(parse = mx_all_commands(parse, string, shell, 0))) {
        return NULL;
    }
    if (!(ast = mx_parse_ast(parse)) || !(*ast)) {
        mx_clear_list_x2(&parse);

        return NULL;
    }

    mx_clear_list_x2(&parse);
    
    return ast;
}
