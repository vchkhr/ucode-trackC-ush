#include "ush.h"

char *mx_user_replace(char *string) {
    int length = 0;

    for (int i = mx_strlen(string) - 1; i > 0; i--, length++) {
        if (string[i] == '/') {
            break;
        }
    }

    return strndup(string, mx_strlen(string) - length);
}
