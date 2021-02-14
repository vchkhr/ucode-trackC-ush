#include "libmx.h"

int mx_strlen_arr(char **strings) {
    if (!strings) {
        return 0;
    }

    int i = 0;

    for (; strings[i];) {
        i++;
    }
    
    return i;
}
