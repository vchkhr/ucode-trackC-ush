#include "ush.h"

char *mx_strdup_index(char *string, int index) {
    for (int i = 0; i <= index; i++) {
        string++;
    }
    
    return strdup(string);
}
