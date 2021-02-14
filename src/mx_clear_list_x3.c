#include "ush.h"

void mx_clear_list_x3(t_ast ***list) {
    t_ast **queue = *list;

    for (int i = 0; queue[i]; i++) {
        mx_clear_list_x2(&queue[i]);
    }
    
    free(queue);
    queue = NULL;
}
