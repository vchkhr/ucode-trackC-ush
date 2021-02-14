#include "ush.h"

void mx_error_print_cd(char *point) {
    mx_printerr("ush: cd: ");
    
    perror(point);
}
