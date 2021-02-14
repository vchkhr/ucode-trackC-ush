#include "ush.h"

char *mx_get_token(char *string, int *i, int *type) {
    int position = 0;
    char *temp = NULL;

    if ((position = mx_index_char_quote(&string[position], ";|&><", "\"\'`$(")) > 0) {
        temp = mx_strndup(string, position);
        *type = mx_get_delimiter(string + position, &position);
        *i += position;
    }
    else if (position == 0) {
        (*i)++;
    }
    else {
        temp = mx_strdup(string);
        *type = 0;
        *i += mx_strlen(string);
    }

    return temp;
}
