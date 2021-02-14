#include "ush.h"

char *mx_user(char *home, char *prefix) {
    char *path = NULL;
    int i = mx_get_char_index_reverse(home, '/');
    struct stat buff;
    struct passwd *pw = getpwuid(getuid());

    if (!home || !*home) {
        path = mx_user_replace(pw->pw_dir);
    }
    else {
        path = mx_strndup(home, i + 1);

        path = mx_strjoin_free(path, prefix);

        if (lstat(path, &buff) != 0) {
            mx_strdel(&path);

            return NULL;
        }
    }

    mx_strdel(&home);

    return path;
}
