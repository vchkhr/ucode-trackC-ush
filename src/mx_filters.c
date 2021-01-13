#include "ush.h"
/*
 * Check if result of subst is correct (NULL or '\0').
 */
static bool check_subsut_result(char **res, char **args, int *i) {
    if (!res[*i]) {
        mx_del_strarr(&res);
        free(args);
        return true;
    }
    else if (res[*i][0] == '\0') {
        mx_strdel(&res[*i]);
        (*i)--;
    }
    return false;
}
/*
 * Get functions and aliases if any.
 */
static char **func_alias_tokens(char *line, t_shell *m_s) {
    char **args = NULL;

    if (mx_strstr(line, "()")) {
        if (mx_get_functions(line, m_s))
            return NULL;
    }
    if (!mx_strncmp(line, "alias", 5) && line[5] && line[5] == ' '
        && line[6] && !mx_isdelim(line[6], MX_USH_TOK_DELIM)) {
        mx_get_aliases(line, m_s);
        return NULL;
    }
    args = mx_parce_tokens(line);
    return args;
}
/*
 * Make substitutions, subst reterns:
 * - subst_tilde      result or res[i] if bad subst;
 * - substr_dollar    result, '\0' or NULL if bad subst;
 * - subst_command    '\0' or NULL if bad subst.
 */
static char **substitutions(char **args, t_shell *m_s) {
    int i;
    int j;
    char **res = NULL;

    res = (char **)malloc((mx_strlen_arr(args) + 1) * sizeof(char *));
    for (i = 0, j = 0; args[j] && args[j][0]; i++, j++) {
        res[i] = mx_strdup(args[j]);
        res[i] = mx_subst_tilde(res[i], m_s->variables);
        res[i] = mx_substr_dollar(res[i], m_s->variables);
        res[i] = mx_subst_command(res[i], m_s);
        if (check_subsut_result(res, args, &i))
            return NULL;
    }
    res[i] = NULL;
    return res;
}

/*
 * Get functions, aliases or parse by USH_TOK_DELIM,
 * subst ~, $,
 *
 * trim'' "" , \.
 *
 * Need scans for word splitting results of parameter expansion
 * and command substitution, that did not double quoted.
 */
char **mx_filters(char *arg, t_shell *m_s) {
    char **args;
    char **res = NULL;

    if (!arg)
        return NULL;
    if ((args = func_alias_tokens(arg, m_s))) {
        if (!(res = substitutions(args, m_s))) {
            mx_strdel(&arg);
            return NULL;
        }
        mx_strtrim_quote(res);
        free(args);
    }
    return res;
}
