#include "ush.h"

int mx_set_1(t_shell *shell, t_process *process) {
    shell->result = 1;
    process->exit_code = 1;
    
    return 1;
}
