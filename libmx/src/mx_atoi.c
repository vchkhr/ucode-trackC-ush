#include "libmx.h"

int mx_atoi(const char *str) {
    if (!str)
        return 0;
    
    int num = 0;

    for (int i = 0; i < mx_strlen(str); i++) {
        if (mx_isdigit(str[i]))
            num = num * 10 + (int)str[i] - 48;
        else
            return 0;
    }

    return num;
}
