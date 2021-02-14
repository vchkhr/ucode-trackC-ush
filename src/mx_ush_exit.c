#include "ush.h"

void mx_ush_exit(t_shell *shell) {
    printf("exit\n");

    mx_clear(shell);
    
    exit(EXIT_SUCCESS);
}
