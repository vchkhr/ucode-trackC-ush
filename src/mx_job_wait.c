#include "ush.h"

int mx_job_wait(t_shell *shell, int job) {
    int status = 0;

    for (int pid = -1, count = 0, amount = mx_get_process(shell, job, 2); count < amount;) {
        pid = waitpid(-shell->jobs[job]->pgid, &status, 0x00000002);
        count++;

        if (MX_WSTAT(status) == 0) {
            mx_process_status(shell, pid, 1);
        }
        else if (MX_WSTAT(status) != 0177 && MX_WSTAT(status) != 0) {
            mx_process_status(shell, pid, 4);
        }
        else if (MX_WSTOPSIG(status)) {
            mx_process_status(shell, pid, 2);

            if (count == amount) {
                mx_jod_status_print(shell, job, 0);
            }
        }
    }

    return status >> 8;
}
