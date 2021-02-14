#include "ush.h"

void mx_key_up(t_shell *shell, char **strings, int *position) {
    if (shell->history[shell->history_index - 1] && shell->history_index > 0) {
        free(*strings);

        *strings = NULL;
        *strings = mx_strnew(1024);

        strcpy(*strings, shell->history[shell->history_index - 1]);

        *position = mx_strlen(*strings);
        shell->history_index--;
    }
}
