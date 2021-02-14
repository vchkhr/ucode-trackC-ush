#include "ush.h"

char *mx_get_var(char *string, int i) {
    char *temp = mx_strndup(string, i);
    char *line = mx_strtrim(temp);

    mx_strdel(&temp);

    if (mx_index_char_quote(line, " \t\r\n\a", NULL) >= 0) {
        mx_strdel(&line);

        return mx_error_syntax("(");
    }
    
    return line;
}
