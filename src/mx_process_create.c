#include "ush.h"

t_process *mx_process_create(t_shell *shell, t_ast *list) {
    t_process *process;
    t_ast *ast = list->previous;
    int index = 0;

    if (!(process = mx_process_initialize(list))) {
        return NULL;
    }
    if (list->previous && (ast->arguments = mx_filters(ast->token, shell)) && *(ast->arguments)) {
        process->redir_delim = ast->type;

        if (ast->type == 5 || ast->type == 6) {
            process->input_path = mx_strdup(ast->arguments[0]);
        }
        else if (ast->type == 7 || ast->type == 8) {
            process->output_path = mx_strdup(ast->arguments[0]);
        }

        for (t_ast *q = list->previous; q; q = q->next) {
            if (q->arguments || ((q->arguments = mx_filters(q->token, shell)) && *(q->arguments))) {
                mx_redirect_append(&process->redirect, q->arguments[0], q->type);
            }
        }
    }
    
    if ((index = mx_command_index(shell, process->arguments_amount[0])) == -1) {
        process->type = -1;
    }
    else {
        process->type = index;
    }
    
    return process;
}
