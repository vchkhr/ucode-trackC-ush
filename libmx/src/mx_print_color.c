#include "libmx.h"

void mx_print_color(char *macros, char *str) {
    mx_printstr(macros);
    mx_printstr(str);
    mx_printstr(RESET);
}
