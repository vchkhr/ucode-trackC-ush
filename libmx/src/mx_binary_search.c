#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
    if (!arr || !s || size <= 0 || !count)
        return -1;

    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        (*count)++;

        int middle = (left + right) / 2;

        if (mx_strcmp(arr[middle], s) == 0)
            return middle;
        else if (mx_strcmp(arr[middle], s) < 0)
            left = middle + 1;
        else
            right = middle - 1;
    }

    (*count) = 0;

    return -1;
}
