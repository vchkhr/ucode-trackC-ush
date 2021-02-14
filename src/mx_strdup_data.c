#include "ush.h"

char *mx_strdup_data(char *string, int index) {
    for (int i = 0; i <= index; i++) {
        string++;
    }
    
    return strdup(string);
}
