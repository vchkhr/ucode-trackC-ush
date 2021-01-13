#include "ush.h"

static void print_left(t_ast *q) {
    for (t_ast *r = q->left; r; r = r->next) {
        mx_printstr("redir == ");
        if (r->type == R_INPUT)
            mx_printstr("< ");
        else if (r->type == R_INPUT_DBL)
            mx_printstr("<< ");
        else if (r->type == R_OUTPUT)
            mx_printstr("> ");
        else if (r->type == R_OUTPUT_DBL)
            mx_printstr(">> ");
        if (r->args)
            mx_print_strarr_in_line(r->args, " ");
        else if (r->token) {
            mx_printstr(q->token);
            mx_printstr("\n");
        }
    }
}

static void print_list(t_ast *parsed_line) {
    for (t_ast *q = parsed_line; q; q = q->next) {
        mx_printstr("proc  == ");
        if (q->args)
            mx_print_strarr_in_line(q->args, " ");
        else if (q->token) {
            mx_printstr(q->token);
            mx_printstr("\n");
        }
        if (q->left)
            print_left(q);
        mx_printstr("delim == ");
        mx_printint(q->type);
        mx_printstr("\n");
    }
}

void mx_ast_print(t_ast **ast) {
    char *j = NULL;
    for (int i = 0; ast[i]; i++) {
        mx_print_color(YEL, "job-");
        j = mx_itoa(i + 1);
        mx_print_color(YEL, j);
        mx_strdel(&j);
        mx_printstr("\n");
        print_list(ast[i]);
    }
    mx_print_color(YEL, "-----\n");
}

t_ast **mx_ast_creation(char *line, t_shell *m_s) {
    t_ast **ast = NULL;
    t_ast *parsed_line = NULL;

    if (!(parsed_line = mx_ush_parsed_line(parsed_line, line, m_s, 0))) {
        return NULL;
    }
    if (!(ast = mx_ast_parse(parsed_line)) || !(*ast)) {
        mx_ast_clear_list(&parsed_line);
        return NULL;
    }
    mx_ast_clear_list(&parsed_line);
    return ast;
}
