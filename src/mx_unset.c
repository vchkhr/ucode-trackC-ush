#include "ush.h"

int mx_unset(t_shell *shell, t_process *process) {
    int options = mx_options_count(process->arguments_amount, "", "unset", " [name ...] ");
    int arguments = mx_arguments_count_unset(process->arguments_amount, options);
    int result = 0;

    if (options <  0 || arguments == 1) {
        return 1;
    }
    else {
        for (int i = options + 1; process->arguments_amount[i] != NULL; i++) {
            mx_error_unset(shell, process->arguments_amount[i], &result);
        }
    }
    
    return result;
}
