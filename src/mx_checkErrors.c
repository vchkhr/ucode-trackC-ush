#include "ush.h"

static char check_quote_auditor(char *s, int *i) {
    int j = *i;
    char tmp;

    if (s[j] == '(' && s[j - 1] && s[j - 1] == '$')
        tmp = ')';
    else if (s[j] == '{' && s[j - 3] && !mx_strncmp(&s[j - 3], "() ", 3))
        tmp = '}';
    else if (s[j] == '(' || s[j] == ')' || s[j] == '{')
        return 0;
    else
        tmp = s[j];
    j++;
    while (s[j] && s[j] != tmp)
        (s[j] == '\\') ? (j += 2) : (j++);
    *i = j;
    (tmp == ')') ? (tmp = '(') : (tmp);
    return tmp;
}

static bool check_quote(char *s) {
    char tmp;

    for (int i = 0; s[i]; i++) {
        if (s[i] == '\\')
            i++;
        else if (mx_isdelim(s[i], "`\"(){")) {
            tmp = check_quote_auditor(s, &i);
            if (tmp && !s[i])
                return mx_unmached_error(tmp);
        }
        else if (s[i] == '\'') {
            i++;
            while (s[i] && s[i] != '\'')
                i++;
            if (!s[i])
                return mx_unmached_error('\'');
        }
    }
    return false;
}

static bool check_parse_auditor(char *line, int i) {
    int i2;
    int i3;

    i2 = mx_get_char_index_quote(&line[i + 1], MX_PARSE_DELIM, MX_QUOTE);
    if (i2 == 0) {
        if (line[i] != line[i + 1] || line[i + 1] == ';')
            return mx_parse_error(&line[i + 1], 1);
        else if (line[i + 2]) {
            i3 = mx_get_char_index_quote(&line[i + 2],
                                         MX_PARSE_DELIM, MX_QUOTE);
            if (i3 == 0)
                return mx_parse_error(&line[i + 2], 1);
        }
    }
    return false;
}

static bool check_parse(char *line) {
    int i = 0;

    while (line) {
        if ((i = mx_get_char_index_quote(line,
            MX_PARSE_DELIM, MX_QUOTE)) >= 0) {
            if ((line[i + 1] == '\0' && line[i] != ';' && line[i] != '&')
                || mx_strcmp(&line[i], "&&") == 0)
                return mx_parse_error("\\n", 2);
            if (line[i + 1])
                if (check_parse_auditor(line, i))
                    return true;
            line += i + 1;
        }
        else
            break;
    }
    return false;
}

bool mx_check_parce_errors(char *line) {
    if (!line || check_quote(line) || check_parse(line))
        return true;
    if (line[0] && mx_isdelim(line[0], "|&><")) {
        if (line[1] && mx_isdelim(line[1], "|&><"))
            return mx_parse_error(&line[0], 2);
        else
            return mx_parse_error(&line[0], 1);
    }
    return false;
}
