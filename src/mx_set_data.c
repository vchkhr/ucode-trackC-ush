#include "ush.h"

void mx_data_set(t_default *environment, char *arguments[]) {
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        if (!environment->environment_options.i) {
            mx_get_set_data(i, environ, environment);
        }
    }

    mx_get_params(environment->parameters, environment->list, environment);

    for (int i = environment->options + 1; i <= environment->options + environment->variables; i++) {
        mx_get_set_data(i, arguments, environment);
    }
}
