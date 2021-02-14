#include "ush.h"

int mx_flag_get(char **arguments) {
    int flag = 1;

    for (int i = 0; arguments[i] != NULL; i++) {
        if (mx_get_char_index(arguments[i],'=') <= 0) {
            flag--;

            break;
        }
    }
    
    return flag;
}
