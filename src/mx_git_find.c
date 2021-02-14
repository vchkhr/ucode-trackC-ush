#include "ush.h"

void mx_git_find(int *flag, char **path, char **user) {
	DIR *directory = opendir(*path);

    for (struct dirent *ds; (ds = readdir(directory)) != 0;) {
        mx_git_get(ds, user, flag, *path);
    }

    char *temp;
    char *real_path = NULL;

    real_path = realpath(*path, NULL);

    if (strcmp(real_path, getenv("HOME")) == 0 || mx_count_substr(real_path, "/") <= 2) {
        (*flag)++;
    }

    free(real_path);
    closedir(directory);

    temp = strdup(*path);
    free(*path);
    
    *path = mx_strjoin(temp, "/..");
    free(temp);
}
