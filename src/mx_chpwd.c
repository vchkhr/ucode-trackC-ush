#include "ush.h"

char *mx_chpwd(char **arguments, int amount, t_shell *shell) {
    char *current = strdup(shell->pwd);
    char *new = NULL;

    if (!mx_strstr(current, arguments[amount + 1])) {
        mx_printerr("ush: cd: string not in pwd: ");
        mx_printerr(arguments[amount + 1]);
        mx_printerr("\n");
    }
    else {
        new = mx_substr_replace_chdir(current, arguments[amount + 1], arguments[amount + 2]);
    }

    free(current);
    
    return new;
}
