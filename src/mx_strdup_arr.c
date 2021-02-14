#include "libmx.h"

char **mx_strdup_arr(char **strings) {
    if (!strings) {
        return NULL;
    }

    char **result = NULL;
    int length = mx_strlen_arr(strings);
    int i = 0;
    
    result = (char **)malloc((length + 1) * sizeof(char *));

    for (; i < length; i++) {
        result[i] = mx_strdup(strings[i]);
    }

    result[i] = NULL;
    
    return result;
}
