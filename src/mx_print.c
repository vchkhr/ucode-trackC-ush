#include "ush.h"

void mx_print(char *command, char *error, char argument) {
    mx_printerr("ush: ");
    mx_printerr(command);

    mx_printerr(": -");
    mx_error_print_char(argument);

    mx_printerr(": invalid option\n");
    mx_printerr(command);

    mx_printerr(": usage: ");
    mx_printerr(command);
    
    mx_printerr(error);
}
