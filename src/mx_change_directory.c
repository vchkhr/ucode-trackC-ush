#include "ush.h"

void mx_change_directory(char *point, t_cd options, t_shell *shell, int *result) {
    char *directory = mx_normalize(point, shell->pwd);
    int flag = mx_path_check_cd(point, options);

    if (!flag) {
        if (chdir(directory) != 0) {
            mx_error_print_cd(point);
            free(directory);
        }
        else {
            mx_mx_environment(directory, shell, options, result);
        }
    }
    else {
        free(directory);
    }

    free(shell->git);

    if (getenv("HOME")) {
        shell->git = mx_git_get_data();
    }
}
