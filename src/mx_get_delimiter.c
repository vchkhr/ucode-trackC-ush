#include "ush.h"

int mx_get_delimiter(char *string, int *position) {
    char *delimiter = NULL;
    int type = 0;

    if (string[0] && mx_isdelim(string[0], ";|&><")) {
        if (string[1] && mx_isdelim(string[1], ";|&><")) {
            delimiter = mx_strndup(string, 2);
        }
        else {
            delimiter = mx_strndup(string, 1);
        }
    }

    type = mx_get_token_type(delimiter);

    if (delimiter) {
        *position += mx_strlen(delimiter);
    }

    mx_strdel(&delimiter);

    return type;
}
