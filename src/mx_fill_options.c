#include "ush.h"

void mx_fill_options(int amount, t_which *options, char **arguments) {
    for (int i = amount; i > 0; i --) {
        for (int j = mx_strlen(arguments[i]); j > 0; j--) {
            if (arguments[i][j] == 'a') {
                options->a = 1;
            }
            if (arguments[i][j] == 's') {
                options->s = 1;
            }
        }
    }
}
