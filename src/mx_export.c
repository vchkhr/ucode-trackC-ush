#include "ush.h"

int mx_export(t_shell *shell, t_process *process) {
    int amount_options = mx_options_count(process->arguments_amount, "p", "export", " [name[=value] ...] or export -p");

    if (amount_options <  0) {
        return 1;
    }

    int amount_arguments = mx_arguments_count_export(process->arguments_amount, amount_options);
    int result = 0;
    
    if (amount_arguments == 1) {
        mx_export_print(shell->exported);
    }
    else {
        for (int i = amount_options + 1; process->arguments_amount[i] != NULL; i++) {
            mx_check_export(process->arguments_amount[i], shell->exported, shell->variables, &result);
        }
    }

    return result;
}
