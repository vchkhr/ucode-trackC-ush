#include "ush.h"

void mx_process_clear(t_process *process) {
    if (!process) {
        return;
    }

    mx_del_strarr(&process->arguments_amount);
    mx_strdel(&process->command);
    mx_strdel(&process->input_path);
    mx_strdel(&process->output_path);
    mx_redirect_clear(&process->redirect);

    if (process->r_infile) {
        free(process->r_infile);
    }
    if (process->r_outfile) {
        free(process->r_outfile);
    }
    
    free(process);
}
