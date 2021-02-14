#include "ush.h"

void mx_check_exit(t_shell *shell, t_process *process) {
    mx_set_variable(shell->variables, "_", process->arguments_amount[0]);
    setenv("_", process->arguments_amount[0], 1);

    if (shell->result == 1 && !(process->type == 10)) {
        shell->result = 0;
    }
}
