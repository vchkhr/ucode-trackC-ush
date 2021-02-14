#include "ush.h"

char *mx_directory(char *pointer, char *pwd) {
    char *directory_current = strdup(pwd);
    char *directory = NULL;
    char **array = NULL;

    if (pointer[0] == '/') {
        directory = strdup(pointer);
    }
    else {
        char *temp = mx_strjoin(directory_current, "/");
        
        free(directory);
        directory = mx_strjoin(temp,pointer);
        free(temp);
    }

    array = mx_get_array(directory);
    free(directory);

    directory = mx_directory_fill(array);
    mx_del_strarr(&array);

    free(directory_current);
    
    return directory;
}
