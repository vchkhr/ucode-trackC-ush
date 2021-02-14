#include "ush.h"

void mx_options_fill_pwd(int amount, t_pwd *pwd, char **arguments) {
    int l = -1;
    int p = -1;

    for (int i = amount; i > 0; i --) {
        for (int j = mx_strlen(arguments[i]); j > 0; j--) {
            if (arguments[i][j] == 'L' && p < 0) {
                l = 1;
            }
            if (arguments[i][j] == 'P' && l < 0) {
                p = 1;
            }
        }
    }
    
    pwd->l = l;
    pwd->p = p;
}
