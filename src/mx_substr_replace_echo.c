#include "ush.h"

char *mx_substr_replace_echo(char *string, char *substring, char *replace) {
    char *result = strdup(string);

    for (; mx_strstr(result,substring) != NULL;) {
        int i = mx_get_substr_index(result,substring);
        char *buff1 = strndup(result, i);
        char *buff2 = mx_strdup_index(result, i + mx_strlen(substring) - 1);

        free(result);

        result = mx_result_get(buff1, buff2, replace);

        free(buff1);
        free(buff2);
    }

    return result;
}
