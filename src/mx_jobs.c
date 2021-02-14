#include "ush.h"

int mx_jobs(t_shell *shell, t_process *process) {
    int options;

    process->exit_code = 0;

    if ((options = mx_options_count(process->arguments_amount, "lrs", "jobs", " [-lrs]")) < 0) {
        process->exit_code = 1;

        return process->exit_code;
    }

    int arguments = mx_arguments_count_jobs(process->arguments_amount, options);
    t_jobs jobs_op = {0, 0, 0};

    mx_job_last(shell);
    mx_options_fill_jobs(options, &jobs_op, process->arguments_amount);

    if (options >= 0 && arguments == 0) {
        for (int i = 0; i < 10000; i++) {
            mx_print_mask(shell, jobs_op, i);
        }
    }
    else if (arguments) {
        mx_jobs_info(shell, process, jobs_op, options);
    }

    return process->exit_code;
}
