#include "ush.h"

static char *check_path(char **arr, char *command) {
    int i = 0;
    char *name = NULL;
    int flag = 0;

    while (arr[i] != NULL && !flag) {
        DIR *dptr  = opendir(arr[i]);
        if (dptr != NULL) {
            struct dirent  *ds;
            while ((ds = readdir(dptr)) != 0) {
                if (strcmp(ds->d_name, command) == 0 && command[0] != '.') {
                    flag++;
                    name = mx_strjoin(arr[i], "/");
                    name = mx_strjoin(name, command);
                    break;
                }
            }
            closedir(dptr);
        }
        i++;
    }
    return name;
}

static char *get_error(char **name, char *command, int *status) {
    char *error = NULL;

    *status = 127;
    if (strstr(command, "/")) {
        *name = command;
        struct stat buff;
        if (lstat(*name, &buff) < 0) {
            error = NULL;
        }
        else {
            if (mx_get_type(buff) == 'd') {
                error = strdup(": is a directory\n");
                *status = 126;
            }
        }
    }
    return error;
}

static void print_error(char *command, char *error) {
    mx_printerr("env: ");
    if (error) {
        mx_printerr(command);
        mx_printerr(error);
        free(error);
    }
    else
        perror(command);
}

static void child_proc(t_process *p, char *path, char **env, int *status) {
    char *const *envp =  env;
    char **arr = mx_strsplit(path, ':');
    char *command = p->argv[0];
    char *error;

    path  = check_path(arr, command);
    if(!path)
        path = strdup(command);
    error = get_error(&path, command, status);
    if (execve(path, p->argv, envp) < 0) {
        print_error(command, error);
        _exit(*status);
    }
    exit(0);
}

int mx_launch_bin(t_process *p, char *path, char **env) {
    pid_t pid;
    int status = 1;

    pid = fork();
    if (pid == 0) {
        child_proc(p, path, env, &status);
    }
    else if (pid < 0)
        perror("env "); 
    else
        waitpid(pid, &status, 0);
    return status >> 8;
}







