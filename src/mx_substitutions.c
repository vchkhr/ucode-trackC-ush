#include "ush.h"

char **mx_substitutions(char **arguments, t_shell *shell) {
    int i = 0;
    char **result = NULL;

    result = (char **)malloc((mx_strlen_arr(arguments) + 1) * sizeof(char *));

    for (int j = 0; arguments[j] && arguments[j][0]; i++, j++) {
        result[i] = mx_strdup(arguments[j]);
        result[i] = mx_substitution_tilde(result[i], shell->variables);
        result[i] = mx_string_dollar(result[i], shell->variables);
        result[i] = mx_substitude_commands(result[i], shell);
        
        if (mx_check_substitution_result(result, arguments, &i)) {
            return NULL;
        }
    }

    result[i] = NULL;
    
    return result;
}
