#include "ush.h"

int mx_get_arguments_amout(char **arguments, int amount_options) {
    int amount = 0;

    for (int i = amount_options + 1; arguments[i] != NULL; i++) {
        amount++;
    }

    if (amount > 2) {
        mx_printerr("ush: cd: too many arguments\n");
    }
    
    return amount;
}
