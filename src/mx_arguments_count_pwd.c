#include "ush.h"

int mx_arguments_count_pwd(char **arguments, int amount) {
    int result = 0;

    for (int i = amount; arguments[i] != NULL; i++) {
        result++;
    }

    if (result > 1 && amount >= 0) {
        mx_printerr("ush: pwd: too many arguments\n");
    }
    
    return result;
}
