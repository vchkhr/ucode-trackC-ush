#include "ush.h"

int mx_pid_check(char *string) {
    for (int j = 0; string[j] != '\0'; j++) {
        if (!(mx_isdigit(string[j]))) {
            return 1;
        }
    }
    
    return 0;
}
