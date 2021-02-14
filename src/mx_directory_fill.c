#include "ush.h"

char *mx_directory_fill(char **array) {
    char *directory = NULL;

    for (int i = 0; array[i] != NULL; i++) {
        if (strcmp(array[i], "") != 0) {
            char *tmp = mx_strjoin(directory, "/");

            if (directory) {
                free(directory);
            }
            
            directory = mx_strjoin(tmp, array[i]);
            free(tmp);
        }
    }

    if (!directory) {
        directory = strdup("/");
    }

    return directory;
}
