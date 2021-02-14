#include "ush.h"

char *mx_shell_run(char *substring, t_shell *shell) {
    int fd1[2];
    int fd2[2];

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int length = strlen(substring) + 1;

    if (write(fd1[1], substring, length) != length) {
        perror("error write to pipe");
    }

    close(fd1[1]);
    mx_strdel(&substring);

    return mx_shell_execute(shell, fd1, fd2);
}
