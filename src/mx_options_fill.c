#include "ush.h"

void mx_options_fill(int amount, t_cd *cd, char **arguments) {
    for (int i = amount; i > 0; i --) {
        for (int j = mx_strlen(arguments[i]); j > 0; j--) {
            if (arguments[i][j] == 'L' && cd->p <= 0) {
                cd->l = 1;
            }
            if (arguments[i][j] == 'P' && cd->l <= 0) {
                cd->p = 1;
            }
            if (arguments[i][j] == 's') {
                cd->s = 1;
            }
        }
    }
}
