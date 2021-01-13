#include "libmx.h"

int mx_strlen_arr(char **s) {
    int i = 0;

    if (!s)
        return 0;
    while (s[i])
        i++;
    return i;
}
