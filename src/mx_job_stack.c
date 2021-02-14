#include "ush.h"

void mx_job_stack(t_shell *shell) {
    t_stack *stack = malloc(sizeof(t_stack));

    stack->first = -1;
    stack->last = -1;
    stack->previous = -1;
    stack->size = 10000;
    stack->stack = malloc(sizeof(int) * 10000);

    for (int i = 0; i < stack->size; i++) {
        stack->stack[i] = 0;
    }
    
    shell->jobs_stack = stack;
}
