#include "ush.h"

char *mx_substr_replace_chdir(char *string, char *substring, char *replace) {
    int index = mx_get_substr_index(string,substring);
    char *buff_1 = strndup(string, index);
    char *buff_2;

    for (int i = 0; i < index + mx_strlen(substring); i++) {
        string++;
    }

    buff_2 = strdup(string);
    
    char *result = mx_strjoin(buff_1, replace);
    char *temp = mx_strjoin(result,buff_2);

    free(result);
    result = strdup(temp);

    free(temp);
    free(buff_1);
    free(buff_2);
    
    return result;
}
