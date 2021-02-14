#include "ush.h"

void mx_backspace_reverse(int *position, char *string) {
    for (int i = *position; i < mx_strlen(string); i++) {
        string[i] = string[i + 1];
    }
}
