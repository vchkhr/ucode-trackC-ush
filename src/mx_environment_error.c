#include "ush.h"

void mx_environment_error(int *flag, int *result, char option) {
    mx_error_print_environment(option, "env: illegal option -- ");
    
    (*result) = -1;
    (*flag)--;
}
