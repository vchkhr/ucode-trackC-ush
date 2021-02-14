#include "ush.h"

char *mx_substitude_quotes(char *s, t_export *var, int *i, int *k) {
    int j = 0;
    int pos = 0;
    char *tmp = NULL;
    char *res = NULL;

    (*i) += *k + 1;
    res = mx_strndup(s, *i);
    j = mx_index_char_quote(&s[*i], "\"", "`$");
    tmp = mx_strndup(&s[*i], j);
    while (tmp && (pos = mx_index_char_quote(tmp, "$", "`$")) >= 0)
        tmp = mx_string_substitution(tmp, var, pos);
    res = mx_strjoin_free(res, tmp);
    res = mx_strjoin_free(res, &s[*i + j]);
    (*i) += mx_strlen(tmp) + 1;
    mx_strdel(&tmp);
    mx_strdel(&s);
    return res;
}
