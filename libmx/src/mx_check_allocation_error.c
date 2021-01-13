#include "libmx.h"

bool mx_check_allocation_error(const void *c) {
    if (c == NULL) {
        mx_printerr_red("allocation error\n");
        return true;
    }
    return false;
}
