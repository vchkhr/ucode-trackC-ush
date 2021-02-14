#include "libmx.h"

bool mx_isdigit(const char c) {
    if (c >= 48 && c <= 57)
        return true;
    
    return false;
}
