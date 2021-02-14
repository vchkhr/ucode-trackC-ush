#include "libmx.h"

char *mx_strcat(char *restrict s1, const char *restrict s2) {
    int size = mx_strlen(s1) + mx_strlen(s2);
    int i = mx_strlen(s1);
    int j = 0;

    while (i < size){
        s1[i] = s2[j];
        i++;
        j++;
    }

    s1[i] = '\0';

    return s1;
}
