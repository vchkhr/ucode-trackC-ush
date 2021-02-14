#include "ush.h"

bool mx_check_token(char *string, char *delimiter) {
    if (!string || !delimiter) {
        return true;
    }

    for (int i = 0; string[i]; i++) {
        if (!mx_isdelim(string[i], delimiter)) {
            return false;
        }
    }
    
    return true;
}
