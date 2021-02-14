#include "ush.h"

void mx_error_arguments(char *argument_0, char *argument_1, char *argument_2, char *argument_3) {
    mx_printerr(argument_0);
    mx_printerr(argument_1);
    mx_printerr(argument_2);
    mx_printerr(argument_3);
}
