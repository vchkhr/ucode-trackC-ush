#include "ush.h"

void mx_error_print_environment(char option, char *error) {
    mx_printerr(error);

    write(2, &option, 1);
    
    mx_printerr("\nusage: env [-iv] [-P utilpath] [-u name]\n");
    mx_printerr("           [name=value ...] [utility [argument ...]]\n");
}
