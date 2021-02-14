#include "ush.h"

char *mx_path_check_process(char **arrays, char *command) {
    char *name = NULL;
    int flag = 0;

    for (int i = 0; arrays[i] != NULL && !flag; i++) {
        mx_directory_process(arrays[i], command, &flag, &name);
    }

    return name;
}
