#include "ush.h"

void mx_default_exec(t_shell *shell, int (*functions[])(t_shell *shell, t_process *process), t_process *process) {
    int original;

    if (process->output_path) {
        original = dup(1);

        if (process->outfile != STDOUT_FILENO) {
            lseek(process->outfile, 0, SEEK_END);
            dup2(process->outfile, STDOUT_FILENO);
            close(process->outfile);
        }
        
        mx_close_dup(process->infile, STDIN_FILENO);
    }

    process->exit_code = functions[process->type](shell, process);
    process->status = 1;
    
    if (process->output_path) {
        if (process->outfile != STDOUT_FILENO) {
            dup2(original, 1);
            close(original);
        }
    }
}
