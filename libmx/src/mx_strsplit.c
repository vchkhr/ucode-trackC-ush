#include "libmx.h"

char **mx_strsplit(const char *s, char c) {
    if (!s)
        return NULL;

    char **arr = (char **)malloc((mx_count_words(s, c) + 1) * sizeof(char *));
    int index = 0;

    while (*s) {
        if (*s != c) {
            int word_length = mx_strnlen(s, c);
            arr[index] = mx_strndup(s, word_length);
            s += word_length;
            index++;

            continue;
        }

        s++;
    }

    arr[index] = NULL;

    return arr;
}
