#include "ush.h"

void mx_key_select(int *position, char **strings, int key, t_shell *shell) {
    if (key >= 127) {
        mx_command_exit(key, position, strings, shell);
    }
    else if (key < 32) {
        mx_signal_execution(key, strings, position, shell);
    }
    else {
        mx_char_add(position, *strings, key, shell);
    }
}
