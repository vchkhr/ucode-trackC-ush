#include "ush.h"

void mx_get_code_exit(t_process *process, int *result, int *flag, int *start){
    if (process->arguments_amount[1][0] == '+' || process->arguments_amount[1][0] == '-') {
        if (process->arguments_amount[1][1] == '\0') {
            (*flag)++;
        }

        (*start)++;
    }

    for (int i = *start; i < mx_strlen(process->arguments_amount[1]); i++) {
        if (!mx_isdigit(process->arguments_amount[1][i])) {
            (*flag)++;
        }
    }

    if (!*flag) {
        *result = atoi(process->arguments_amount[1]);
    }
    else {
        mx_printerr("ush: exit: ");
        mx_printerr(process->arguments_amount[1]);
        mx_printerr(": numeric argument required\n");
        
        *result = 255;
    }
}
