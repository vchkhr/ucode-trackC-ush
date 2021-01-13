#include "ush.h"

static char *usage_err(void) {
    mx_printerr("ush: function usage: func() { ...; }\n");
    return NULL;
}

static char *get_var(char *line, int i) {
    char *tmp = mx_strndup(line, i);
    char *var = mx_strtrim(tmp);

    mx_strdel(&tmp);
    if (mx_get_char_index_quote(var, MX_USH_TOK_DELIM, NULL) >= 0) {
        mx_strdel(&var);
        return mx_syntax_error("(");
    }
    return var;
}

static char *get_value(char *line, int end) {
    int i = end;
    char *value = NULL;

    if (!line[i] || mx_strncmp(&line[i], " { ", 3) != 0)
        return usage_err();
    i += 3;
    end = mx_get_char_index_quote(&line[i], "}", "\"\'`$(");
    if (end <= 0)
        return mx_syntax_error("{");
    value = mx_strndup(&line[i], end);
    return value;
}

bool mx_get_functions(char *line, t_shell *m_s) {
    char *var;
    char *value;
    int i = mx_get_char_index_quote(line, "(", "\"\'`$");

    if (line[i + 1] && line[i + 1] == ')') {
        if (!(var = get_var(line, i)))
            return true;
        if (!(value = get_value(line, i + 2))) {
            mx_strdel(&var);
            return true;
        }
        if (m_s->functions)
            mx_set_variable(m_s->functions, var, value);
        else
            mx_push_export(&m_s->functions, var, value);
        mx_strdel(&var);
        mx_strdel(&value);
        return true;
    }
    return false;
}
