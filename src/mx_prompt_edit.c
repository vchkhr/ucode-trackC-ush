#include "ush.h"

void mx_prompt_edit(t_shell *shell) {
    if (shell->prompt) {
        free(shell->prompt);
    }
    if (!shell->prompt_status) {
        mx_customize(shell);
    }
    else {
        if (mx_var(shell, "PROMPT")) {
            shell->prompt = strdup(mx_var(shell, "PROMPT"));
        }
        else {
            shell->prompt = strdup("u$h");
        }
    }
}
