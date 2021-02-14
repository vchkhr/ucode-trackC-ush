#include "ush.h"

void mx_char_add(int *position, char *string, int keycode, t_shell *shell) {
    if (mx_strlen(string) >= shell->line_len) {
        shell->line_len += 1024;
        string = realloc(string, shell->line_len);
    }

    for (int i = mx_strlen(string); i > *position; i--) {
        string[i] = string[i - 1];
    }
    
    string[*position] = keycode;
    (*position)++;
}
