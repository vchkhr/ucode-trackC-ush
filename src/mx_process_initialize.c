#include "ush.h"

t_process *mx_process_initialize(t_ast *list) {
    t_process *process = (t_process *)malloc(sizeof(t_process));

    if (!process) {
        return NULL;
    }

    process->arguments_amount = mx_strdup_arr(list->arguments);
    process->delim = list->type;
    process->command = mx_strdup(list->arguments[0]);

    process->input_path = NULL;
    process->output_path = NULL;
    process->redirect = NULL;

    process->redir_delim = 0;
    process->foregrd = 1;
    process->pipe = 0;

    process->r_infile = (int *) malloc(sizeof(int) * 1);
    process->r_outfile = (int *) malloc(sizeof(int) * 1);

    if (process->delim == 1) {
        process->foregrd = 0;
    }
    else if (process->delim == 4) {
        process->pipe = 1;
    }

    process->next = NULL;

    return process;
}
