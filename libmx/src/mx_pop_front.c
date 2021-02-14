#include "libmx.h"

void mx_pop_front(t_list **list) {
    if (!list || !(*list))
        return;

    t_list *next = (*list)->next;

    free((*list));
    (*list) = next;
}
