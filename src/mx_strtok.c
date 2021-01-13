#include "ush.h"

static char *get_end_usual_quote_func(char *s, const char *delim, char *end) {
    while (*s && !(mx_isdelim(*s, (char *)delim))) {
        if (*s == '\\')
            s += 2;
        else if (*s == '\'')
            s += mx_get_char_index(s + 1, '\'') + 2;
        else if (mx_isdelim(*s, "\""))
            s += mx_get_char_index_quote(s + 1, "\"", "`$") + 2;
        else if (mx_isdelim(*s, "`"))
            s += mx_get_char_index_quote(s + 1, "`", "\"\'$(") + 2;
        else if (mx_strncmp(s, "$(", 2) == 0)
            s += mx_get_char_index_quote(s + 2, ")", MX_QUOTE) + 3;
        else if (mx_strncmp(s, "() {", 4) == 0)
            s += mx_get_char_index_quote(s + 4, "}", MX_QUOTE) + 5;
        else
            s++;
    }
    end = s;
    return end;
}

static char *strtok_tmp (char *s, const char *delim, char **save_ptr) {
    char *end = NULL;

    if (s == NULL)
        s = *save_ptr;
    s += strspn(s, delim);  // Scan leading delimiters
    if (*s == '\0') {
        *save_ptr = s;
        return NULL;
    }
    if (!(end = get_end_usual_quote_func(s, delim, end)))
        return NULL;
    if (*end == '\0') {  // If it's last token, int tne end of the str
        *save_ptr = end;
        return s;
    }
    *end = '\0';  // Terminate the token
    *save_ptr = end + 1;
    return s;
}

char *mx_strtok (char *s, const char *delim) {
    static char *olds;
    return strtok_tmp (s, delim, &olds);
}
