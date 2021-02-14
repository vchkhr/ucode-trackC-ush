#include "ush.h"

void mx_git_get(struct dirent *ds, char **user, int *flag, char *path) {
    if (strcmp(ds->d_name, ".git") == 0) {
        char *git_path = mx_strjoin(path, "/.git/HEAD");
        char *git = mx_file_to_str(git_path);
        char **arr = mx_strsplit(git, '/');

        if (arr != NULL) {
            int count = 0;

            for (; arr[count] != NULL; ) {
                count++;
            }

            arr[count - 1][mx_strlen(arr[count - 1]) - 1] = '\0';

            if (mx_count_substr(arr[count - 1], "\n") == 0) {
                *user = strdup(arr[count - 1]);
            }
            
            (*flag)++;
            mx_del_strarr(&arr);
        }

        free(git);
        free(git_path);
    }
}
