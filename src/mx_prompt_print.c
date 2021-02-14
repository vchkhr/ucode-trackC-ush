#include "ush.h"

void mx_prompt_print(t_shell *shell) {
    if (!shell->prompt_status) {
        printf("%s", "\x1B[1;35m");
    }

    printf("%s", shell->prompt);

    if (!shell->prompt_status && shell->git) {
        printf(" %sgit:(%s%s%s)", "\x1B[1;34m", "\x1B[31m", shell->git, "\x1B[1;34m");
    }

    if (!shell->prompt_status) {
        printf("%s", "\x1B[0m");
    }

    printf("> ");
    fflush(NULL);
}
