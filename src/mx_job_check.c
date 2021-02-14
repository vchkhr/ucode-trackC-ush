#include "ush.h"

void mx_job_check(t_shell *shell) {
    pid_t pid;

    for (int status, job_id; (pid = waitpid(-1, &status, 0x00000001 | 0x00000002 | 0x00000010)) > 0;) {
        if (MX_WSTAT(status) == 0) {
            mx_process_status(shell, pid, 1);
        }
        else if ((MX_WSTAT(status) == 0177 && MX_WSTOPSIG(status) != 0x13)) {
            mx_process_status(shell, pid, 2);
        }
        else if ((MX_WSTAT(status) == 0177 && MX_WSTOPSIG(status) == 0x13)) {
            mx_process_status(shell, pid, 3);
        }

        job_id = mx_job_id_by_pid(shell, pid);
        
        if (job_id > 0 && mx_job_completed(shell, job_id)) {
            mx_jod_status_print(shell, job_id, 0);
            mx_remove_job(shell, job_id);
        }
    }
}
