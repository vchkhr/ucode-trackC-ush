#include "ush.h"

int mx_declare(t_shell *shell, t_process *process) {
    int result = shell->exit_code;
    int amount = mx_options_count_set(process->arguments_amount);

    if (amount == 1 && mx_strcmp(process->arguments_amount[1], "-f") == 0) {
        for (t_export *q = shell->functions; q; q = q->next) {
            mx_printstr(q->name);
            mx_printstr(" () {\n\t");
            mx_printstr(q->value);
            mx_printstr("\n}\n");
        }
    }

    return result;
}
