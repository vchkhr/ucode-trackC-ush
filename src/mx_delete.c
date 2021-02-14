#include "ush.h"

void mx_delete(char **array, int n) {
    free(array[n]);

    array[n] = strdup("");

    for (int j = n; j >= 0; j--) {
        if (strcmp(array[j], "") != 0) {
            free(array[j]);
            array[j] = strdup("");
            
            break;
        }
    }
}
