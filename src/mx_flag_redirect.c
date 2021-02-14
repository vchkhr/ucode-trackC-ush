#include "ush.h"

int mx_flag_redirect(int delimiter) {
    int flags = 0;

    if (delimiter == 7) {
        flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    if (delimiter == 8) {
        flags = O_WRONLY | O_CREAT;
    }
    
    return flags;
}
