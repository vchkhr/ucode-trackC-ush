#include "libmx.h"

bool mx_isdelim (char c, char *delim) {
    if (!c || !delim)
        return false;
    for (int i = 0; delim[i]; i++) {
        if (delim[i] == c)
            return true;
    }
    return false;
}
