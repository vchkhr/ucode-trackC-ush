#include "ush.h"
/*
 * Substitution functions.
 */
static void func_or_push(t_ast **res, char *arg, int type, t_shell *m_s) {
    t_export *q;
    char *tmp = mx_strdup(arg);
    char *args0 = mx_strtok(tmp, MX_USH_TOK_DELIM);

    for (q = m_s->functions; q; q = q->next)
        if (mx_strcmp(args0, q->name) == 0 && !mx_strstr(q->value, args0)) {
            mx_strdel(&tmp);
            *res = mx_ush_parsed_line(*res, q->value, m_s, type);
            return;
        }
    for (q = m_s->aliases; q; q = q->next)
        if (mx_strcmp(args0, q->name) == 0 && !mx_strstr(q->value, args0)) {
            mx_strdel(&tmp);
            *res = mx_ush_parsed_line(*res, q->value, m_s, type);
            return;
        }
    mx_strdel(&tmp);
    mx_ast_push_back(res, arg, type);
}
/*
 * if alias or func keep last type correct.
 */
static void if_recurcion_func_or_alias(t_ast **res, int old_t) {
    if (old_t) {
        t_ast *q = *res;
        while (q->next)
            q = q->next;
        q->type = old_t;
    }
}
/*
 * Check if token consists of delimeters.
 */
static bool isempty(char *s, char *delim) {
    if (!s || !delim)
        return true;
    for (int i = 0; s[i]; i++) {
        if (!mx_isdelim(s[i], delim))
            return false;
    }
    return true;
}
/*
 * Get list of all commands and delimeters (operators) -> use filters.
 */
t_ast *mx_ush_parsed_line(t_ast *res, char *line1, t_shell *m_s, int old_t) {
    int type = 0;
    int i = 0;
    char *tmp = NULL;
    char *line;

    if (mx_check_parce_errors(line1))
        return NULL;
    line = mx_strdup(line1);
    while (line[i])
        if ((tmp = mx_get_token_and_delim(&line[i], &i, &type))) {
            if (!isempty(tmp, MX_USH_TOK_DELIM))
                func_or_push(&res, tmp, type, m_s);
            else if (type != SEP)
                return mx_parse_error_ush(type, res, line);
            free(tmp);
        }
    mx_strdel(&line);
    if_recurcion_func_or_alias(&res, old_t);
    return res;
}
