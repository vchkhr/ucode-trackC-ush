#include "ush.h"

void mx_customize(t_shell *shell) {
    char *info = NULL;
    int count = 0;
    char **array = NULL;

    if (strcmp(shell->pwd, "/") == 0) {
        info = strdup("/");
    }
    else if (getenv("HOME") && strcmp(shell->pwd, getenv("HOME")) == 0) {
        info = strdup("~");
    }
    else {
        array = mx_strsplit(shell->pwd, '/');

        for (count = 0; array[count] != NULL;) {
            count++;
        }

        info = strdup(array[count - 1]);
        mx_del_strarr(&array);
    }
    
    shell->prompt = strdup(info);
    free(info);
}
