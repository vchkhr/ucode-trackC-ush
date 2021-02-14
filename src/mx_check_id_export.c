#include "ush.h"

int mx_check_id_export(char *argument) {
    int flag = 0;
    int length = mx_get_char_index(argument, '=');

    if (length == 0) {
        flag++;
    }

    for (int j = 0; j < length; j++) {
        if (!isalpha(argument[j]) && !isdigit(argument[j]) && argument[j] != '_') {
            flag++;
        }
    }
    
    return flag;
}
