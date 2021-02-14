#include "ush.h"

int mx_command_cd(t_shell *shell, t_process *process) {
    t_cd cd = {0, 0, 0};
    int options_amount = mx_options_count(process->arguments_amount, "sLP", "cd", " [-s] [-L|-P] [dir]");
    int arguments_amount = mx_get_arguments_amout(process->arguments_amount, options_amount);
    char *pointer = NULL;
    int result = 1;

    mx_options_fill_cd(options_amount, &cd, process->arguments_amount);

    if (options_amount >= 0 && arguments_amount < 3) {
        if (arguments_amount == 0) {
            pointer = mx_home();
        }
        else if (arguments_amount == 2) {
            pointer = mx_chpwd_cd(process->arguments_amount, options_amount, shell);
        }
        else {
            pointer = mx_next(process, options_amount);
        }
        
        if (pointer) {
            mx_change_directory(pointer, cd, shell, &result);
        }

        free(pointer);
    }
    
    return result;
}
