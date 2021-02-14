#include "ush.h"

int mx_set_0(t_shell *shell, t_process *process) {
    shell->result = 0;
    process->exit_code = 0;

    return 0;
}
