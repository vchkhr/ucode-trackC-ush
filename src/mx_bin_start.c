#include "ush.h"

int mx_bin_start(t_process *process, char *path, char **environment) {
    pid_t pid;
    int status = 1;

    pid = fork();
    if (pid == 0) {
        mx_process_bin(process, path, environment, &status);
    }
    else if (pid < 0)
        perror("env "); 
    else
        waitpid(pid, &status, 0);
    return status >> 8;
}
