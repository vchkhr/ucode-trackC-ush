#include "ush.h"

void mx_mx_environment(char *directory, t_shell *shell, t_cd cd, int *result) {
    char *link = malloc(1024);

    readlink(directory, link, 1024);

    if (cd.p == 1 && strcmp(link, "") != 0) {
        free(directory);
        directory = getcwd(NULL, 1024);
    }

    free(link);
    setenv("OLDPWD", shell->pwd, 1);

    mx_set_variable(shell->variables, "OLDPWD", shell->pwd);
    mx_set_variable(shell->exported, "OLDPWD", shell->pwd);

    setenv("PWD", directory, 1);
    
    mx_set_variable(shell->variables, "PWD", directory);
    mx_set_variable(shell->exported, "PWD", directory);

    free(shell->pwd);
    shell->pwd = strdup(directory);
    free(directory);

    *result = 0;
}
