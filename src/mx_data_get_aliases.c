#include "ush.h"

void mx_data_get_aliases(char *argument, char **name, char **value) {
    int index = mx_get_char_index(argument, '=');
    int length = 0;

    *name = mx_strndup(argument, index);
    
    if (argument[index + 1] == '\"') {
        length = mx_strlen(&argument[index + 2]);
        *value = mx_strndup(&argument[index + 2], length - 1);
    }
}
