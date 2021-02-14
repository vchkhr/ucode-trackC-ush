#include "ush.h"

void mx_print_arguments(char **results, const char *delimiter) {
    if (!results || !delimiter) {
        return;
    }
    if (results[0] == NULL) {
        mx_printstr("NULL\n");
    }

    for (int i = 0; results[i] != NULL; i++) {
        mx_printstr(results[i]);

        if (results[i + 1] != NULL) {
            mx_printstr(delimiter);
        }
    }
}
