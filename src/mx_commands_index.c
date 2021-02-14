#include "ush.h"

int mx_command_index(t_shell *shell, char *command) {
    for (int i = 0; shell->default_list[i] != NULL; i++) {
        if (strcmp(command, shell->default_list[i]) == 0) {
            return i;
        }
    }

    return -1;
}
