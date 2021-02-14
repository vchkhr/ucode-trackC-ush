#include "libmx.h"

int mx_bubble_sort(char **arr, int size) {
    int swaper = 0;

    for (int i = 0; i < size - 1; i++)
        for (int j = 0; j < size - i - 1; j++)
            if (mx_strcmp(arr[j], arr[j + 1]) > 0) {
                char *text = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = text;

                swaper++;
            }

    return swaper;
}
