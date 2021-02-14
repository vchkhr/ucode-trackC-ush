#include "ush.h"

char *mx_tilde_result(char *string, t_export *export) {
    char *result = NULL;
    struct passwd *pw = getpwuid(getuid());

    for (t_export *q = export; q; q = q->next) {
        if (mx_strcmp(string, q->name) == 0) {
            result = q->value;
        }
    }

    if (!result) {
        if (mx_strcmp(string, "HOME") == 0) {
            return strdup(pw->pw_dir);
        }
        else {
            return NULL;
        }
    }
    
    return mx_strdup(result);
}
