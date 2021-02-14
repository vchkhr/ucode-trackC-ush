#include "ush.h"

char *mx_git_get_data() {
    char *user = NULL;
    char *path = strdup(".");

    for (int flag = 0; !flag;) {
        mx_git_find(&flag, &path, &user);
    }

    free(path);

    return user;
}
