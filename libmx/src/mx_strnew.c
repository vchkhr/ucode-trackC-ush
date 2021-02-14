#include "libmx.h"

char *mx_strnew(int size) {
    if (size < 0)
        return NULL;

    char *new_str = (char *) malloc(sizeof(char) * (size + 1));

    for (int i = 0; i <= size; i++)
        new_str[i] = '\0';

    return new_str;
}
