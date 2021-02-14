#include "ush.h"

char *mx_combine_strings(char *string, int position, t_shell *shell) {
    char *result = NULL;
    int length = 0;
    char *sub_string = NULL;

    result = mx_strndup(string, position);

    if ((sub_string = mx_substritution(&string[position], &length))) {
        sub_string = mx_shell_run(sub_string, shell);
        result = mx_strjoin_free(result, sub_string);

        if (sub_string) {
            mx_strdel(&sub_string);
        }
    }
    
    if (string[position + length + 1]) {
        result = mx_strjoin_free(result, &string[position + length + 1]);
    }

    mx_strdel(&string);
    
    return result;
}
