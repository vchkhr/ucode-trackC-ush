#include "ush.h"

void mx_error_unset(t_shell *shell, char *argument, int *result) {
    int flag = mx_id_check(argument);

    if (flag) {
        mx_printerr("ush: unset: `");
        mx_printerr(argument);
        mx_printerr("': not a valid identifier\n");

        return;
    }
    
    mx_name_delete(&shell->exported, argument);
    mx_name_delete(&shell->variables, argument);
    unsetenv(argument);
    result = 0;
}
