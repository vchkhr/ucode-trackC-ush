#include "ush.h"

void mx_options_fill_echo(char **arguments, t_echo *echo, int amount) {
    for (int i = amount; i >= 0; i--) {
        for (int j = mx_strlen(arguments[i]); j >= 1; j--) {
            if (arguments[i][j] == 'n') {
                echo->n = 1;
            }
            else if (arguments[i][j] == 'e') {
                if (!echo->E) {
                    echo->e = 1;
                }
            }
            else if (arguments[i][j] == 'E') {
                if (!echo->e) {
                    echo->E = 1;
                }
            }
        }
    }
}
