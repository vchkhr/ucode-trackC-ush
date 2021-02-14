#include "ush.h"

void mx_get_params(t_export *parameters, t_export *environment, t_default *env) {
    for (t_export *head = parameters; head != NULL; head = head->next) {
        if (strcmp(head->name, "u") == 0) {
            mx_names_delete(&environment, head->value);
        }
        if (strcmp(head->name, "P") == 0) {
            if (env->path != NULL) {
                free(env->path);
            }
            
            env->path = strdup(head->value);
        }
    }
}
