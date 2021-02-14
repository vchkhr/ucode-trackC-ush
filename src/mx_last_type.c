#include "ush.h"

void mx_last_type(t_ast **ast, int old) {
    if (old) {
        t_ast *queue = *ast;

        for (; queue->next;) {
            queue = queue->next;
        }
        
        queue->type = old;
    }
}
