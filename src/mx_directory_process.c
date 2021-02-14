#include "ush.h"

void mx_directory_process(char *directory, char *command, int *flag, char **name) {
    DIR *directory_pointer  = opendir(directory);

    if (directory_pointer != NULL) {
        for (struct dirent *dirent; (dirent = readdir(directory_pointer)) != 0;) {
            if (strcmp(dirent->d_name, command) == 0 && command[0] != '.') {
                char *temp = mx_strjoin(directory, "/");

                (*flag)++;
                *name = mx_strjoin(temp, command);

                free(temp);

                break;
            }
        }
        
        closedir(directory_pointer);
    }
}
