#include "ush.h"

int mx_get_process(t_shell *shell, int job, int filter) {
    t_process *process;
    int count = 0;

    if (job > 10000 || shell->jobs[job] == NULL) {
        return -1;
    }

    for (process = shell->jobs[job]->first_pr; process != NULL; process = process->next) {
        if (filter == 0 || (filter == 1 && process->status == 1) || (filter == 2 && process->status != 1)) {
            count++;
        }
    }
    
    return count;
}
