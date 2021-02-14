#include "ush.h"

void mx_path_check_command_info(char **array, char *command, t_list **output, int *flag) {
    char *name = NULL;
    struct dirent *ds;

    for (int i = 0; array[i] != NULL; i++) {
        DIR *dptr = opendir(array[i]);

        if (dptr != NULL) {
            for (; (ds = readdir(dptr)) != 0;) {
                if (strcmp(ds->d_name, command) == 0 && command[0] != '.') {
                    name = strcat(array[i], "/");
                    name = strcat(name, command);

                    mx_push_back(&*output, name);

                    (*flag)++;
                }
            }
            
            closedir(dptr);
        }
    }
}
