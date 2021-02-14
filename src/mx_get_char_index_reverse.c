#include "libmx.h"

int mx_get_char_index_reverse(const char *string, char character) {
    if (!string || !*string) {
        return -2;
    }

    char *new_string = (char *)string;
    
    for (int i = mx_strlen(new_string) - 1; new_string[i]; i--) {
        if (new_string[i] == character) {
            return i;
        }
    }

    return -1;
}
