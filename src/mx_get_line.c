#include "ush.h"

char *mx_get_line(t_shell *shell) {
    char *string;
    struct termios safe;
    int out = dup(1);
    int devtty = open("/dev/tty", O_WRONLY);

    dup2(devtty, 1);
    mx_prompt_edit(shell);

    safe = mx_term_disable();
    shell->line_len = 1024;

    mx_prompt_print(shell);
    string = mx_get_keys(shell);

    if (shell->history_count == shell->history_size) {
        shell->history_size += 1000;
        shell->history = (char **)realloc(shell->history, shell->history_size);
    }
    if (strcmp(string, "") != 0) {
        shell->history[shell->history_count] = strdup(string);
        shell->history_count++;
    }

    shell->history_index = shell->history_count;
    mx_term_enable(safe);

    dup2(out, 1);
    close(out);
    close(devtty);

    return string;
}
