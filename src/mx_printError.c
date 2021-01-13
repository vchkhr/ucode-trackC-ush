#include "ush.h"

bool mx_parse_error(char *c, int k) {
    mx_printerr("ush: parse error near `");
    write(2, c, k);
    mx_printerr("\'\n");
    return true;
}

bool mx_unmached_error(char c) {
    if (c == '\"' || c == '\'') {
        mx_printerr("Odd number of quotes.\n");
        return true;
    }
    else {
        mx_printerr("Unmatched ");
        write(2, &c, 1);
        mx_printerr(".\n");
        return true;
    }
}

char *mx_syntax_error(char *c) {
    mx_printerr("ush: syntax error near unexpected token `");
    mx_printerr(c);
    mx_printerr("'\n");
    return NULL;
}

static char *get_delim_from_type(int type) {
    if (type == SEP)
        return mx_strdup(";");
    else if (type == FON)
        return mx_strdup("&");
    else if (type == AND)
        return mx_strdup("&&");
    else if (type == OR)
        return mx_strdup("||");
    else if (type == PIPE)
        return mx_strdup("|");
    else if (type == R_INPUT)
        return mx_strdup("<");
    else if (type == R_INPUT_DBL)
        return mx_strdup("<<");
    else if (type == R_OUTPUT)
        return mx_strdup(">");
    else if (type == R_OUTPUT_DBL)
        return mx_strdup(">>");
    return NULL;
}

t_ast *mx_parse_error_ush(int type, t_ast *res, char *line) {
    char *delim;

    if (type != SEP) {                      // works "; ; ;", block "; | ;"
        delim = get_delim_from_type(type);
        mx_printerr("ush: parse error near `");
        write(2, delim, mx_strlen(delim));
        mx_strdel(&delim);
        mx_printerr("\'\n");
    }
    mx_ast_clear_list(&res);
    mx_strdel(&line);
    return NULL;
}
