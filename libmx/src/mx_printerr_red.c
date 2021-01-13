#include "libmx.h"

void mx_printerr_red(char *c) {
    mx_printerr(RED);
    mx_printerr(c);
    mx_printerr(RESET);
}
