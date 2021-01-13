#include "libmx.h"

char **mx_strdup_arr(char **strarr) {
    char **res = NULL;
    int len;
    int i = 0;

    if (!strarr)
        return NULL;
    len = mx_strlen_arr(strarr);
    res = (char **)malloc((len + 1) * sizeof(char *));
    for (; i < len; i++) {
        res[i] = mx_strdup(strarr[i]);
    }
    res[i] = NULL;
    return res;
}
