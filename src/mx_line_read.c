#include "ush.h"

char *mx_line_read(t_shell *shell) {
    char *string = mx_strnew(1);
    char *result = NULL;
    size_t buffer_size = 0;

    if (getline(&string, &buffer_size, stdin) < 0) {
        if (!isatty(0)) {
            shell->exit_code = 0;
            mx_clear(shell);

            exit(0);
        }
    }

    if (string[0] != '\0'){
        result = mx_strdup(string);
        mx_strdel(&string);
    }
    
    return result;
}
