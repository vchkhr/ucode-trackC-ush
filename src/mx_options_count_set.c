#include "ush.h"

int mx_options_count_set(char **arguments) {
    int amount = 0;

    for (int i = 1; arguments[i]; i++) {
        amount++;
    }
    
    return amount;
}
