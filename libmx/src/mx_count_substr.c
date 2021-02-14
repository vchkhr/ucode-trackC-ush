#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
    if (!str || !sub)
        return -1;
    
    int counter = 0;
    const char *temp = str;

    while (mx_strstr(temp, sub)) {
        temp = mx_strstr(temp, sub);
        temp += mx_strlen(sub);
        counter++;
    }

    return counter;
}
