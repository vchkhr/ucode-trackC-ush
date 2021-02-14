#include "ush.h"

int mx_builting_start(t_shell *shell, t_process *process, int job_id) {
    int (*functions[])(t_shell *shell, t_process *process) = {&mx_environment, &mx_export, &mx_unset, &mx_echo, &mx_jobs, &mx_fg, &mx_pid, &mx_command_cd, &mx_pwd, &mx_find, &mx_exit, &mx_set, &mx_kill, &mx_directory_change, &mx_set_0, &mx_alias, &mx_declare, &mx_set_1, NULL};
    process->status = 0;

    if (process->pipe || !process->foregrd) {
        mx_default_fork(shell, job_id, functions, process);
    }
    else {
        mx_default_exec(shell, functions, process);
    }
    
    return process->exit_code;
}
