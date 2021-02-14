#include "ush.h"

void mx_options_fill_jobs(int amount, t_jobs *jobs, char **arguments) {
    for (int i = amount; i > 0; i--) {
        for (int j = mx_strlen(arguments[i]); j > 0; j--) {
            if (arguments[i][j] == 'l') {
                jobs->left = 1;
            }
            if (arguments[i][j] == 'r') {
                jobs->right = 1;
            }
            if (arguments[i][j] == 's') {
                jobs->stop = 1;
            }
        }
    }
}
