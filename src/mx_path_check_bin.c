#include "ush.h"

char *mx_path_check_bin(char **arrays, char *command) {
    char *name = NULL;

    for (int i = 0, flag = 0; arrays[i] != NULL && !flag; i++) {
        DIR *dptr  = opendir(arrays[i]);

        if (dptr != NULL) {
            struct dirent *ds;

            for (; (ds = readdir(dptr)) != 0;) {
                if (strcmp(ds->d_name, command) == 0 && command[0] != '.') {
                    flag++;

                    name = mx_strjoin(arrays[i], "/");
                    name = mx_strjoin(name, command);

                    break;
                }
            }

            closedir(dptr);
        }
    }
    
    return name;
}
