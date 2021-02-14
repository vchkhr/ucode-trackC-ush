#include "libmx.h"

void mx_pop_back(t_list **list) {
    if (!list || !(*list))
        return;
    if (!(*list)->next) {
        free((*list));
        (*list) = NULL;
        return;
    }
    
    t_list *cpy = (*list);
        
    while (cpy->next->next)
        cpy = cpy->next;

    free(cpy->next);
    cpy->next = NULL;
}
