#include "ush.h"

void mx_stack_push(t_shell *shell, int job) {
    if (shell->jobs_stack->first < shell->jobs_stack->size) {
        shell->jobs_stack->stack[++shell->jobs_stack->first] = job;
    }
}
