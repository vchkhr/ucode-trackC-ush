#include "libmx.h"

bool mx_isdelim (char character, char *delimiter) {
    if (!character || !delimiter) {
        return false;
    }

    for (int i = 0; delimiter[i]; i++) {
        if (delimiter[i] == character) {
            return true;
        }
    }

    return false;
}
