#include "ush.h"

int mx_pwd(t_shell *shell, t_process *proccess) {
    t_pwd pwd_options = {0, 0};
    int options = mx_options_count(proccess->arguments_amount, "LP", "pwd", " [-LP]");
    int arguments = mx_arguments_count_pwd(proccess->arguments_amount, options);

    mx_options_fill_pwd(options, &pwd_options, proccess->arguments_amount);

    if (options <  0 || arguments > 1) {
        return 1;
    }

    char *dir = getcwd(NULL, 1024);
    int result = 1;

    if (dir != NULL) {
        mx_pwd_print(dir, &result, shell, pwd_options);
    }
    else {
        perror("ush: pwd");
    }
    
    return result;
}
