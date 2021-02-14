#include "ush.h"

int mx_arguments_count_kill(char **arguments) {
    int result = 0;

    for (int i = 1; arguments[i] != NULL; i++) {
        result++;
    }
    
    return result;
}
