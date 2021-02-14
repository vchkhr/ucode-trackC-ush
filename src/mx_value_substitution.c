#include "ush.h"

char *mx_value_substitution(char *string, t_export *variables) {
    for (t_export *q = variables; q; q = q->next) {
        if (mx_strcmp(string, q->name) == 0) {
            return q->value;
        }
    }

    return NULL;
}
