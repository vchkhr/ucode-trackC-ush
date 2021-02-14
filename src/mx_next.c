#include "ush.h"

char *mx_next(t_process *process, int amount) {
    char *point = NULL;

    if (strcmp(process->arguments_amount[amount + 1], "-") == 0) {
        point = mx_previous();
    }
    else {
        point = strdup(process->arguments_amount[amount + 1]);
    }
    
    return point;
}
