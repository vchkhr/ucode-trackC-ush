#include "ush.h"

void mx_print_command(t_shell *shell, char *string, int position, int length) {
    for (int i = position; i <= mx_strlen(string); i++) {
        printf(" ");
    }
    for (int i = 0; i <= length + 2; i++) {
        printf("\b\x1b[2K");
    }

    printf("\r");
    mx_prompt_print(shell);
    printf("%s", string);

    for (int i = 0; i < mx_strlen(string) - position; i++) {
        printf("%c[1D", 27);
    }

    fflush(NULL);
}
