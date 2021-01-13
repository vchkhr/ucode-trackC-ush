#include "ush.h"

static void mx_get_char_auditor(char *s, int *ii, char *q) {
    int i = *ii;
    char tmp;

    if ((mx_isdelim(s[i], q) && s[i] == '`')
        || (mx_isdelim(s[i], q) && s[i] == '\"')) {
        tmp = s[i];
        i++;
        while (s[i] && s[i] != tmp)
            (s[i] == '\\') ? (i += 2) : (i++);
    }
    else if (mx_isdelim(s[i], q) && s[i] == '\'') {
        i++;
        while (s[i] && s[i] != '\'')
            i++;
    }
    *ii = i;
}

int mx_get_char_index_quote(char *s, char *c, char *q) {  // q = "\"\'`$"
    if (!s || !c)
        return -2;
    for (int i = 0; s[i]; i++) {
        if (s[i] == '\\')
            i++;
        else if (mx_isdelim(s[i], q) && !mx_strncmp(&s[i], "$(", 2))
            while (s[i] && s[i] != ')')
                (s[i] == '\\') ? (i += 2) : (i++);
        else if (mx_isdelim(s[i], q) && !mx_strncmp(&s[i], "() {", 4))
            while (s[i] && s[i] != '}')
                (s[i] == '\\') ? (i += 2) : (i++);
        else if (mx_isdelim(s[i], q) && mx_isdelim(s[i], "`\'\""))
            mx_get_char_auditor(s, &i, q);
        else
            for (int j = 0; j < mx_strlen(c); j++)
                if (s[i] == c[j])
                    return i;
    }
    return -1;
}

static void mx_strtrim_quote_auditor(char *s, char *tmp, int *ii, int *jj) {
    int i = *ii;
    int j = *jj;

    if (s[i] == '\"') {
        i++;
        for (; s[i] && s[i] != '\"'; i++, j++) {
            if (s[i] == '\\' && mx_isdelim(s[i + 1], MX_DBLQ_EXCEPTIONS))
                i++;
            tmp[j] = s[i];
        }
        j--;
    }
    else if (s[i] == '\'') {
        i++;
        for (; s[i] && s[i] != '\''; i++, j++)
            tmp[j] = s[i];
        j--;
    }
    *ii = i;
    *jj = j;
}

void mx_strtrim_quote(char **str) {
    char *tmp = NULL;
    int i = 0;
    int j = 0;

    for (int k = 0; str[k]; k++) {
        char *s = str[k];
        tmp = mx_strnew(mx_strlen(s));
        for (i = 0, j = 0; s[i]; i++, j++) {
            if (s[i] && s[i] == '\\') {
                i++;
                tmp[j] = s[i];
            }
            else if (s[i] && (s[i] == '\"' || s[i] == '\''))
                mx_strtrim_quote_auditor(s, tmp, &i, &j);
            else
                tmp[j] = s[i];
        }
        mx_strdel(&str[k]);
        str[k] = tmp;
    }
}
