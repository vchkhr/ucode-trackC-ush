#include "ush.h"

char *mx_shell_execute(t_shell *shell, int *fd1, int *fd2) {
    extern char **environ;
    pid_t pid;
    char *result = NULL;

    if ((pid = fork()) < 0) {
        perror("error fork");
    }
    else if (pid > 0) {
        result = mx_parent_shell(shell, fd1, fd2, pid);
    }
    else {
        mx_dup2(fd1, fd2);

        if (execve(shell->kernal, NULL, environ) < 0) {
            perror("ush ");
            _exit(EXIT_SUCCESS);
        }

        exit(EXIT_SUCCESS);
    }
    
    return result;
}
