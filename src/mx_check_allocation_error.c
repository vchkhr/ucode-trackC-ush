#include "libmx.h"

bool mx_check_allocation_error(const void *character) {
    if (character == NULL) {
        mx_printerr_red("allocation error\n");

        return true;
    }
    
    return false;
}
