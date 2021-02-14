#include "ush.h"

char *mx_error_process(char **name, char *command, int *status) {
    char *error = NULL;

    *status = 127;

    if (strstr(command, "/")) {
        struct stat buff;

        *name = command;
        
        if (lstat(*name, &buff) < 0) {
            error = NULL;
        }
        else {
            if (mx_get_file_stat(buff) == 'd') {
                error = strdup("is a directory: ");
                *status = 126;
            }
        }
    }
    else {
        error = strdup("command not found: ");
    }
    
    return error;
}
