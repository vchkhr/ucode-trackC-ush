#include "ush.h"

int mx_get_next_job_id(t_shell *shell) {
    for (int i = 1; i < shell->max_number_job + 1; i++) {
        if (shell->jobs[i] == NULL) {
            return i;
        }
    }
    
    return -1;
}
