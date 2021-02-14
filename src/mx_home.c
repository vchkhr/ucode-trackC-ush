#include "ush.h"

char *mx_home() {
    char *point = NULL;

    if (getenv("HOME")) {
        point = strdup(getenv("HOME"));
    }
    else {
        mx_printerr("ush: cd: HOME not set\n");
    }
    
    return point;
}
