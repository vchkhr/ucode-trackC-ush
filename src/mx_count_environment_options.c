#include "ush.h"

int mx_count_environment_options(char **arguments, t_default *environment) {
    int amount = 0;

    for (int i = 1; arguments[i] != NULL; i++, amount++) {
        if (arguments[i][0] != '-') {
            break;
        }
        if (strcmp(arguments[i], "--") == 0) {
            amount++;

            break;
        }

        int valid = mx_option_add(arguments, &i, &amount, environment);

        if (valid < 0) {
            return -1;
        }
    }

    return amount;
}
