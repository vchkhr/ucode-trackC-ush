#include "libmx.h"

void mx_push_back(t_list **list, void *data) {
    if (!data)
        return;

    t_list *back = mx_create_node(data);

    if (!list || !(*list)) {
        (*list) = back;
        return;
    }

    t_list *cpy = (*list);
        
    while (cpy->next)
        cpy = cpy->next;

    cpy->next = back;
}
