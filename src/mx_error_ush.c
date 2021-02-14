#include "ush.h"

t_ast *mx_error_ush(int type, t_ast *result, char *string) {
    char *delimiter;

    if (type != 0) {
        delimiter = mx_delimiter_error_print(type);

        mx_printerr("ush: parse error near `");
        write(2, delimiter, mx_strlen(delimiter));

        mx_strdel(&delimiter);
        mx_printerr("\'\n");
    }

    mx_clear_list_x2(&result);
    mx_strdel(&string);
    
    return NULL;
}
