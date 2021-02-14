#include "ush.h"

int mx_path_check_cd(char *point, t_cd options) {
    int flag = 0;
    char *read = realpath(point, NULL);

    if (options.s && read && strcmp(point, read) != 0) {
        mx_printerr("ush: cd: ");
        mx_printerr(point);
        mx_printerr(": Not a directory");
        mx_printerr("\n");

        flag++;
    }

    free(read);
    
    return flag;
}
