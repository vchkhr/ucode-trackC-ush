#include "ush.h"

void mx_data_get_set_parameter(char *argument, char **name, char **value) {
    int index = mx_get_char_index(argument, '=');
 
    *name = strndup(argument, index);
    *value = mx_strdup_parameter(argument, index);
}
