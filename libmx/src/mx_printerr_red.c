#include "libmx.h"

void mx_printerr_red(char *string) {
    mx_printerr("\x1B[31m");
    mx_printerr(string);
    mx_printerr("\x1B[0m");
}
