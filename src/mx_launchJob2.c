#include "ush.h"

void mx_dup_fd(t_process *p) {
    if (p->r_infile[0] != STDIN_FILENO) {
        dup2(p->r_infile[0], STDIN_FILENO);
        close(p->r_infile[0]);
    }
    if (p->r_outfile[0] != STDOUT_FILENO) {
        dup2(p->r_outfile[0], STDOUT_FILENO);
        close(p->r_outfile[0]);
    }
    if (p->errfile != STDERR_FILENO) {
        dup2(p->errfile, STDERR_FILENO);
        close(p->errfile);
    }
}

void mx_print_fd(t_process  *p) {
    printf("\x1B[32m p->r_input \x1B[0m\t");
    for(int i = 0; i < p->c_input; i ++) {
        printf("\x1B[32m [%d] \x1B[0m  \t", p->r_infile[i]);
    }
    printf("\n");
    printf("\x1B[32m p->r_output \x1B[0m\t");
    for(int i = 0; i < p->c_output; i ++) {
        printf("\x1B[32m [%d] \x1B[0m  \t", p->r_outfile[i]);
    }
    printf("\n");
}
