#include "ush.h"

int mx_arguments_count_chdir(char **arguments, int amount) {
    int result = 0;

    for (int i = amount + 1; arguments[i] != NULL; i++) {
        result++;
    }
    
    if (result > 2) {
        mx_printerr("ush: cd: too many arguments\n");
    }

    return result;
}
