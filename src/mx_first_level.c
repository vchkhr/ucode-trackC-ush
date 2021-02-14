#include "ush.h"

int mx_first_level(t_ast *queue) {
    int i = 1;

    for (; queue; queue = queue->next) {
        if (queue->type == 0 || queue->type == 1 || queue->type == 2 || queue->type == 3) {
            i++;
        }
    }
    
    return i;
}
