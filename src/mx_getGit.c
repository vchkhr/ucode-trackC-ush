#include "ush.h"

static void get_git(struct dirent  *ds, char **user, int *flag, char *path) {
    if (strcmp(ds->d_name, ".git") == 0) {
        char *gitpath = mx_strjoin(path, "/.git/HEAD");
        char *git = mx_file_to_str(gitpath);
        char **arr = mx_strsplit(git, '/');
        int count = 0;

        if (arr != NULL) {
            while (arr[count] != NULL)
                count++;
            arr[count - 1][mx_strlen(arr[count - 1]) - 1] = '\0';
            if (mx_count_substr(arr[count - 1], "\n") == 0)
                *user = strdup(arr[count - 1]);
            (*flag)++;
            mx_del_strarr(&arr);
        }
        free(git);
        free(gitpath);
    }
}

static void find_git(int *flag, char **path, char **user) {
	DIR *dptr  = opendir(*path);
    struct dirent  *ds;
    char *real_path = NULL;
    char *tmp;

    while ((ds = readdir(dptr)) != 0) {
        get_git(ds, user, flag, *path);
    }
    real_path = realpath(*path, NULL);
    if (strcmp(real_path, getenv("HOME")) == 0 ||
        mx_count_substr(real_path, "/") <= 2)
        (*flag)++;
    free(real_path);
    closedir(dptr);
    tmp = strdup(*path);
    free(*path);
    *path = mx_strjoin(tmp, "/..");
    free(tmp);
}

char *mx_get_git_info(void) {
    char *user = NULL;
    int flag = 0;
    char *path = strdup(".");

    while(!flag) {
        find_git(&flag, &path, &user);
    }
    free(path);
    return user;
}
