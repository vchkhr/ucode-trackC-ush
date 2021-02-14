#include "ush.h"

int mx_alias(t_shell *shell, t_process *process) {
    int amount = mx_options_count_set(process->arguments_amount);
    int result = shell->exit_code;

    if (amount == 0) {
        for (t_export *q = shell->aliases; q; q = q->next) {
            mx_printstr(q->name);
            mx_printstr("='");
            mx_printstr(q->value);
            mx_printstr("'\n");
        }
    }
    
    return result;
}
