#include "ush.h"

int mx_arguments_count_unset(char **arguments, int amount) {
    int result = 0;

    for (int i = amount; arguments[i] != NULL; i++) {
        result++;
    }

    return result;
}
