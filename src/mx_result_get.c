#include "ush.h"

char *mx_result_get(char *buff1, char *buff2,  char *replace) {
    char *temp = strdup(buff1);
    char *result = mx_strjoin(temp, replace);

    free(temp);

    temp = strdup(result);
    free(result);

    result = mx_strjoin(temp, buff2);
    free(temp);

    return result;
}
