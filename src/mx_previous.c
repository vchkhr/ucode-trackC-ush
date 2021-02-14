#include "ush.h"

char *mx_previous() {
    char *point = NULL;

    if (getenv("OLDPWD")) {
        point = strdup(getenv("OLDPWD"));
    }
    else {
        mx_printerr("ush: cd: OLDPWD not set\n");
    }
    
    return point;
}
