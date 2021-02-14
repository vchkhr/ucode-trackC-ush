#include "ush.h"

void mx_input_read(int *length, int *key, char *string) {
    *length = mx_strlen(string);
    *key = 0;
    
    read(0, key, 4);
}
