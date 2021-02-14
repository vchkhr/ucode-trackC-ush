#include "ush.h"

int mx_echo(t_shell *shell, t_process *process) {
    shell->result = 0;

    int result = 0;
    int amount = mx_options_count_echo(process->arguments_amount);

    mx_edit_arguments(amount, process);
    
    return result;
}
