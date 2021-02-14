#include "ush.h"

int mx_options_count(char **arguments, char *options, char *command, char *error) {
    int amount = 0;

    for (int i = 1; arguments[i] != NULL; i++, amount++) {
        if (arguments[i][0] != '-' || strcmp(arguments[i], "-") == 0) {
            break;
        }
        if (strcmp(arguments[i], "--") == 0) {
            amount++;

            break;
        }

        for (int j = 1; j < mx_strlen(arguments[i]); j++) {
            if (mx_get_char_index(options,arguments[i][j]) < 0) {
                mx_print(command, error, arguments[i][j]);
                
                return -1;
            }
        }
    }

    return amount;
}
