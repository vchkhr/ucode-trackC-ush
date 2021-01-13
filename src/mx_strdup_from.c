#include "ush.h"

char *mx_strdup_from(char *str, int index) {
    for (int i = 0; i <= index; i++) {
        str++;
    }
    return strdup(str);
}
