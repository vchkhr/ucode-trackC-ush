#include "ush.h"

int mx_directory_change(t_shell *shell, t_process *process) {
    t_cd options_cd = {0, 0, 0};
    int amount_options = mx_options_count(process->arguments_amount, "sLP", "chdir", " [-s] [-L|-P] [dir]");
    int amount_arguments = mx_arguments_count_chdir(process->arguments_amount, amount_options);
    char *point = NULL;
    int result = 1;

    mx_options_fill(amount_options, &options_cd, process->arguments_amount);

    if (amount_options >= 0 && amount_arguments < 3) {
        if (amount_arguments == 0) {
            point = mx_home();
        }
        else if (amount_arguments == 2) {
            point = mx_chpwd(process->arguments_amount, amount_options, shell);
        }
        else {
            point = mx_next(process, amount_options);
        }
        if (point) {
            mx_change_directory(point, options_cd, shell, &result);
        }

        free(point);
    }
    
    return result;
}
