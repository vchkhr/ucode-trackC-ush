#include "ush.h"

int mx_options_count_echo(char **arguments) {
    int amount = 0;

    for (int i = 1; arguments[i] != NULL; i++, amount++) {
        if (arguments[i][0] == '-' ) {
            if (!strchr("neE",arguments[i][1])) {
                break;
            }
        }
        else {
            break;
        }
    }

    return amount;
}
