#include "ush.h"

char *mx_get_keys(t_shell *shell) {
    char *string = mx_strnew(1024);

    for (int key = 0, length = 0, position = 0; key != 10 && key != 3;) {
        mx_prompt_edit(shell);
        mx_input_read(&length, &key, string);
        length += mx_strlen(shell->prompt);

        if (shell->git) {
            length += mx_strlen(shell->git) + 7;
        }

        mx_key_select (&position, &string, key, shell);

        if (key != 3) {
            mx_print_command(shell, string, position, length);
        }
    }

    return string;
}
