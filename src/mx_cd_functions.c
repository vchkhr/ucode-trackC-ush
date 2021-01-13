#include "ush.h"

char *mx_go_somewere(t_process *p, int n_options) {
    char *point = NULL;

    if (strcmp(p->argv[n_options + 1], "-") == 0)
        point = mx_go_back();
        else
        point = strdup(p->argv[n_options + 1]);
    return point;
}

char *mx_go_back(void) {
    char *point = NULL;

    if (getenv("OLDPWD"))
        point = strdup(getenv("OLDPWD"));
    else
        mx_printerr("ush: cd: OLDPWD not set\n");
    return point;
}

char *mx_go_home(void) {
    char *point = NULL;

    if (getenv("HOME"))
        point = strdup(getenv("HOME"));
    else
        mx_printerr("ush: cd: HOME not set\n");
    return point;
}
