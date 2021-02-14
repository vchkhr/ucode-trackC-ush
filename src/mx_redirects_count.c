#include "ush.h"

void mx_redirects_count(t_process *process) {
    t_redir *redir;

    process->c_input = 0;
    process->c_output = 0;
    
    for (redir = process->redirect; redir; redir = redir->next) {
        if (redir->delimiter == 5 || redir->delimiter == 6) {
            process->c_input += 1;
        }
        if (redir->delimiter == 7 || redir->delimiter == 8) {
            process->c_output += 1;
        }
    }

    if (process->c_input == 0) {
        process->c_input++;
    }
    if (process->c_output == 0) {
        process->c_output++;
    }
    
    process->r_outfile = (int *) realloc(process->r_outfile, sizeof(int) * (process->c_output));
}
