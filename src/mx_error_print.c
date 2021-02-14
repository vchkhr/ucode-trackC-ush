#include "ush.h"

void mx_error_print(char *command, char *error) {
    mx_printerr("ush: ");

    if (error) {
        mx_printerr(command);
        mx_printerr(error);
    }
    else {
        perror(command);
    }
}
