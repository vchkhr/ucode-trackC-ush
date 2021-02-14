#include "ush.h"

void mx_clear(t_shell *shell) {
    mx_export_clear(shell->exported);
    mx_export_clear(shell->variables);
    mx_export_clear(shell->functions);
    mx_export_clear(shell->aliases);
    mx_del_strarr(&shell->history);
    
    free(shell->kernal);
    free(shell->pwd);
}
