#include "ush.h"

char **mx_get_array(char *directory) {
    char **arrays = NULL;

    arrays = mx_strsplit(directory, '/');

    for (int i = 0; arrays[i] != NULL; i++) {
        if (strcmp(arrays[i], ".") == 0) {
            free(arrays[i]);
            arrays[i] = strdup("");
        }
        if (strcmp(arrays[i], "..") == 0) {
            mx_delete (arrays, i);
        }
    }

    return arrays;
}
