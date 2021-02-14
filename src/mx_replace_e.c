#include "ush.h"

void mx_replace_e(int *i, char *str) {
    if (str[*i] == '\\' && str[*i + 1] == 'e') {
        if (str[*i + 2] != '\\') {
            (*i) += 3;
        }
        else {
            (*i) += 2;
        }
    }
}
