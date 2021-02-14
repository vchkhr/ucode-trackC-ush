#include "ush.h"

void mx_stack_pop(t_shell *shell, int job) {
    int size = shell->jobs_stack->size;
    int *temp = malloc(sizeof(int) * size);
    int i = 0;

    for (; i < size; i++) {
        temp[i] = shell->jobs_stack->stack[i];
    }
    for (i = 0; i < size; i ++) {
        shell->jobs_stack->stack[i] = 0;
    }

    if (shell->jobs_stack->first >= 0) {
        for (int i = 0, j = 0; j < size; i++, j++) {
            if (temp[i] == job) {
                i++;
            }

            shell->jobs_stack->stack[j] = temp[i];
        }
    }

    shell->jobs_stack->first--;

    free(temp);
}
