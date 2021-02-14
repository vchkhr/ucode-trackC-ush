#include "ush.h"

void mx_data_clear(char *name, char *value) {
    if (name) {
        free(name);
    }

    if (value) {
        free(value);
    }
}
