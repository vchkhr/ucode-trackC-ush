#include "ush.h"

t_job *mx_job_create(t_shell *shell, t_ast *list) {
    t_process *process = NULL;

    for (t_ast *l = list; l; l = l->next) {
        if ((l->arguments = mx_filters(l->token, shell)) && *(l->arguments)) {
            mx_process_append(&process, shell, l);
        }
        else {
            mx_process_clear(process);

            return NULL;
        }
    }

    return mx_job_init(process);
}
