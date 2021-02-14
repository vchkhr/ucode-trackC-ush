#include "ush.h"

void mx_dup2(int *fd1, int *fd2) {
    if (fd1[0] != STDIN_FILENO) {
        if (dup2(fd1[0], STDIN_FILENO) != STDIN_FILENO) {
            perror("error dup2 stdin");
        }

        close(fd1[0]);
    }

    if (fd2[1] != STDOUT_FILENO) {
        if (dup2(fd2[1], STDOUT_FILENO) != STDOUT_FILENO) {
            perror("error dup2 stdout");
        }
        
        close(fd2[1]);
    }
}
