#include "ush.h"

bool mx_error_parse(char *buffer, int count) {
    mx_printerr("ush: parse error near `");
    write(2, buffer, count);
    mx_printerr("\'\n");

    return true;
}
