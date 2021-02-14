#include "ush.h"

void mx_error_print_export(char *arg, int *exit_code) {
    mx_printerr("ush: export: `");
    mx_printerr(arg);
    mx_printerr("': not a valid identifier\n");
    
    *exit_code = 1;
}
