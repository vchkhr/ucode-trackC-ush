#include "ush.h"

int mx_exit(t_shell *shell, t_process *process) {
    if (process->arguments_amount[1] != NULL && process->arguments_amount[2] != NULL) {
        mx_printerr("ush: exit: too many arguments\n");
    }
    else if (shell->jobs_stack->first && shell->result == 0) {
        mx_printerr("ush: you have suspended jobs.\n");

        shell->result = 1;
    }
    else {
        int start = 0;
        int flag = 0;
        int exit_code = shell->exit_code;

        if (process->arguments_amount[1] != NULL) {
            mx_get_code_exit(process, &exit_code, &flag, &start);
        }

        mx_clear(shell);
        exit(exit_code);
    }

    return 1;
}
