#include "libmx.h"

int mx_strlen_arr(char **string) {
    if (!string) {
        return 0;
    }

    int i = 0;

    for (; string[i];) {
        i++;
    }
    
    return i;
}
