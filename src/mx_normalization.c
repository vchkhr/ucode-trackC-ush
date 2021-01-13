#include "ush.h"

static void delete_dd (char **arr, int i) {
    free(arr[i]);
    arr[i] = strdup("");
    for (int j = i; j >= 0; j --) {
        if (strcmp(arr[j], "") != 0) {
            free(arr[j]);
            arr[j] = strdup("");
            break;
        }
    }
}

static char **get_arr(char *dir) {
    char **arr = NULL;
    int i = 0;

    arr = mx_strsplit(dir, '/');
    while (arr[i] != NULL) {
        if (strcmp(arr[i], ".") == 0) {
            free(arr[i]);
            arr[i] = strdup("");
        }
        if (strcmp(arr[i], "..") == 0)
            delete_dd (arr, i);
        i++;
    }
    return arr;
}

static char *fill_dir(char **arr) {
    int i = 0;
    char *dir = NULL;

    while (arr[i] != NULL) {
        if (strcmp(arr[i], "") != 0) {
            char *tmp = mx_strjoin(dir, "/");
            if (dir)
                free(dir);
            dir = mx_strjoin(tmp, arr[i]);
            free(tmp);
        }
        i++;
    }
    if (!dir)
        dir = strdup("/");

    return dir;
}

static char *get_dir(char *point, char *pwd) {
    char *cur_dir = strdup(pwd);
    char *dir = NULL;
    char **arr = NULL;

    if (point[0] == '/')
        dir = strdup(point);
    else {
        char *tmp = mx_strjoin(cur_dir, "/");
        free(dir);
        dir = mx_strjoin(tmp,point);
        free(tmp);
    }
    arr = get_arr(dir);
    free(dir);
    dir = fill_dir(arr);
    mx_del_strarr(&arr);
    free(cur_dir);
    return dir;
}


char *mx_normalization (char *point, char *pwd) {
    char *str = NULL;

    str = get_dir(point, pwd);
    return str;
}
