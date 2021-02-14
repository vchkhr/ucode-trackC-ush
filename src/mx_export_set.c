#include "ush.h"

t_export *mx_export_set() {
    t_export *export = NULL;
    extern char **environ;

    for (size_t i = 0; environ[i] != NULL; i++) {
        int index = mx_get_char_index(environ[i],'=');
        char *name = strndup(environ[i],index);
        char *value = mx_strdup_data(environ[i],index);

        if (strcmp(name, "_") != 0) {
            mx_export_push(&export, name, value);
        }
        if (name) {
            free(name);
        }
        if (value) {
            free(value);
        }
    }
    
    return export;
}
