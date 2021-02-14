#include "ush.h"

t_export *mx_var_set() {
    t_export *export = NULL;
    extern char **environ;

    for (size_t i = 0; environ[i] != NULL; i++) {
        int idx = mx_get_char_index(environ[i], '=');
        char *name = strndup(environ[i], idx);
        char *value = mx_strdup_data(environ[i], idx);

        mx_export_push(&export, name, value);

        if (name) {
            free(name);
        }
        if (value) {
            free(value);
        }
    }

    mx_export_push(&export, "?", "0");
    
    return export;
}
