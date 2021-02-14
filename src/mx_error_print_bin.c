#include "ush.h"

void mx_error_print_bin(char *command, char *error) {
    mx_printerr("env: ");

    if (error) {
        mx_printerr(command);
        mx_printerr(error);

        free(error);
    }
    else {
        perror(command);
    }
}
