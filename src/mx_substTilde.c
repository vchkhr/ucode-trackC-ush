#include "ush.h"
/*
 * Get value and check if variable does not unset.
 */
static char *get_res(char *var, t_export *variables) {
    char *res = NULL;
    struct passwd *pw = getpwuid(getuid());

    for (t_export *q = variables; q; q = q->next)
        if (mx_strcmp(var, q->name) == 0)
            res = q->value;
    if (!res) {
        if (mx_strcmp(var, "HOME") == 0) {
            return strdup(pw->pw_dir);
        }
        else
            return NULL;
    }
    return mx_strdup(res);
}
/*
 * Prefix - all after ~ and before char '/' or '\0' (example: ~mboiko/).
 */
static char *get_prefix(char *s, int *sleshpos) {
    char *prefix = NULL;
    int sp = -1;

    if (s[1]) {
        sp = mx_get_char_index_quote(&s[1], "/", MX_QUOTE);
        if (sp > 0)
            prefix = mx_strndup(&s[1], sp);
        else
            prefix = mx_strdup(&s[1]);
    }
    *sleshpos = sp;
    return prefix;
}
/*
 * Substitutiont tilde in different ways.
 */
static char *expantion(char *s, t_export *v) {
    char *res = NULL;
    int sleshpos;
    char *prefix = get_prefix(s, &sleshpos);

    if (prefix == NULL)
        res = get_res("HOME", v);
    else if (prefix[0] == '/' && sleshpos == 0)
        res = get_res("HOME", v);
    else if (prefix[0] == '+' && !prefix[1])
        res = get_res("PWD", v);
    else if (mx_strcmp(prefix, "-") == 0)
        res = get_res("OLDPWD", v);
    else
        res = mx_add_login(get_res("HOME", v), prefix);
    if (res && sleshpos >= 0)
        res = mx_strjoin_free(res, &s[sleshpos + 1]);
    mx_strdel(&prefix);
    return res;
}
/*
 * Substitutiont tilde.
 */
char *mx_subst_tilde(char *s, t_export *variables) {
    char *res = NULL;

    if (!s || !*s)
        return s;
    if (s[0] == '~') {
        res = expantion(s, variables);
        if (res) {
            mx_strdel(&s);
            return res;
        }
    }
    return s;
}
