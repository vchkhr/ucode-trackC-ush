#include "ush.h"

char *mx_get_parameter(char **arguments, int *i, int j, int *amount) {
    char *parameter = NULL;

    if (arguments[*i][j + 1] != '\0') {
        parameter = mx_strdup_index(arguments[*i], j);
    }
    else if (arguments[*i + 1]) {
        parameter = strdup(arguments[*i + 1]);

        (*amount)++;
        (*i)++;
    }
    
    return parameter;
}
