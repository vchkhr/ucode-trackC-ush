#include "libmx.h"

int mx_count_words(const char *str, char c) {
    bool state = true;
    int wordcount = 0;
    
    if (str == NULL)
        return -1;

    while (*str) {
        if (*str == c)
            state = true;
        else if (state) {
            state = false;
            wordcount++;
        }

        str++;
    }

    return wordcount;
}
