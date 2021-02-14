#include "ush.h"

void mx_defaults(t_shell *shell) {
    char *bad_list[19] = {"env", "export", "unset", "echo", "jobs", "fg", "bg", "cd", "pwd", "which", "exit", "set", "kill", "chdir", "true", "alias", "declare", "false", NULL};

    shell->default_list = (char **) malloc(sizeof(char *) * 19);

    for (int i = 0; i < 19; i++) {
        shell->default_list[i] = bad_list[i];
    }

    shell->max_number_job = 1;
    shell->result = 0;
    shell->history_count = 0;
    shell->history_size = 1000;
    shell->history = (char **)malloc(sizeof(char *) * shell->history_size);

    for (int i = -1; i < 10000; ++i) {
        shell->jobs[i] = NULL;
    }

    shell->functions = NULL;
    shell->aliases = NULL;
    
    mx_job_stack(shell);
    mx_path_set(shell);
}
