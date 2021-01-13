#include "ush.h"
/*
 * Check if prefix is correct login or not.
 */

static char *replace(char *str) {
    char *res = NULL;
    int len = 0;

    for(int i = mx_strlen(str) - 1; i > 0; i--) {
        if (str[i] == '/')
            break;
        len++;
    }
    res = strndup(str, mx_strlen(str) - len);
    return res;
}

char *mx_add_login(char *home, char *prefix) {
    char *path = NULL;
    int i = mx_get_char_index_reverse(home, '/');
    struct stat buff;
    struct passwd *pw = getpwuid(getuid());

    if (!home || !*home) {
        path = replace(pw->pw_dir);
    }
    else
        path = mx_strndup(home, i + 1);
    path = mx_strjoin_free(path, prefix);
    if (lstat(path, &buff) != 0) {
        mx_strdel(&path);
        return NULL;
    }
    mx_strdel(&home);
    return path;
}
