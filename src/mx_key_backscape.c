#include "ush.h"

void mx_key_backscape(int *position, char *string) {
    if (*position > 0) {
        for (int i = *position - 1; i < mx_strlen(string); i++) {
            string[i] = string[i + 1];
        }
        
        (*position)--;
    }
}
