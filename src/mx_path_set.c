#include "ush.h"

void mx_path_set(t_shell *shell) {
    char *directory = getcwd(NULL, 256);
    char *path = NULL;

    shell->kernal = mx_strjoin(directory, "/ush");

    if (!getenv("PATH")) {
        path = strdup("/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:");
        path = mx_strjoin_free(path, "/usr/local/munki");
    }
    else {
        path = strdup(getenv("PATH"));
    }

    setenv("PATH", path, 1);
    
    free(path);
    free(directory);
}
