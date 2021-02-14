#include "ush.h"

char **mx_filters(char *argument, t_shell *shell) {
    if (!argument) {
        return NULL;
    }

    char **arguments;
    char **result = NULL;
    
    if ((arguments = mx_get_alias_tokens(argument, shell))) {
        if (!(result = mx_substitutions(arguments, shell))) {
            mx_strdel(&argument);

            return NULL;
        }

        mx_trim_quote(result);
        free(arguments);
    }
    
    return result;
}
