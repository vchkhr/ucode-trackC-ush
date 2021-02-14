#include "ush.h"

int mx_count_arguments(char **arguments, int amount) {
    int amount_arguments = 0;

    for (int i = amount + 1; arguments[i] != NULL; i++) {
        amount_arguments++;
    }
    
    return amount_arguments;
}
