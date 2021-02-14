#include "ush.h"

void mx_error_print_char(const char buffer) {
    write(2, &buffer, 1);
}
