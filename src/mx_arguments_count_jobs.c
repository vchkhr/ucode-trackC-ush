#include "ush.h"

int mx_arguments_count_jobs(char **arguments, int amount) {
    int result = 0;

    for (int i = amount + 1; arguments[i] != NULL; i++) {
        result++;
    }
    
    return result;
}
