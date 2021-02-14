#include "ush.h"

void mx_command_exit(int keycode, int *position, char **string, t_shell *shell) {
    if (keycode == 4479771) {
        if (*position > 0) {
            (*position)--;
        }
    }
    else if (keycode == 4414235) {
        if (*position < mx_strlen(*string)) {
            (*position)++;
        }
    }
    else if (keycode == 4610843) {
        *position = mx_strlen(*string);
    }
    else if (keycode == 4741915) {
        *position = 0;
    }
    else if (keycode == 4348699 || keycode == 2117491483) {
        mx_key_down(shell, string, position);
    }
    else if (keycode == 4283163 || keycode == 2117425947) {
        mx_key_up(shell, string, position);
    }
    else if (keycode == 42946) {
        if (shell->prompt_status) {
            shell->prompt_status--;
        }
        else {
            shell->prompt_status++;
        }
        
        mx_prompt_edit(shell);
    }
    else if (keycode == 127) {
        mx_key_backscape(position, *string);
    }
}
