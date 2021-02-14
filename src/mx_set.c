#include "ush.h"

int mx_set(t_shell *shell, t_process *process) {
    int result = shell->exit_code;
    int amount = mx_options_count_set(process->arguments_amount);

    if (amount == 0) {
        for (t_export *q = shell->variables; q; q = q->next) {
            mx_printstr(q->name);
            mx_printstr("=");

            mx_printstr(q->value);
            mx_printstr("\n");
        }
    }
    
    return result;
}
