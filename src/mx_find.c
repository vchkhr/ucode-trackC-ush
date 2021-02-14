#include "ush.h"

int mx_find(t_shell *shell, t_process *process) {
    t_which options = {0, 0};

    int amount = mx_options_count(process->arguments_amount, "as", "which", " [-as] program ...");

    mx_fill_options(amount, &options, process->arguments_amount);

    if (amount < 0) {
        return 1;
    }

    int result = 0;
    
    for (int i = amount + 1, flag = 0; process->arguments_amount[i] != NULL; i++) {
        mx_info_command(shell, process->arguments_amount[i], &flag, options);

        if (!flag) {
            result = 1;
        }
    }

    return result;
}
