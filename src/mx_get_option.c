#include "ush.h"

char *mx_get_option(char character) {
    char *option = malloc(2);

    option[0] = character;
    option[1] = '\0';
    
    return option;
}
