#include "libmx.h"

void mx_clear_list (t_list **list) {
    if (list == NULL || *list == NULL) {
        return;
    }

    t_list *first = *list;

    if (!first) {
        return;
    }

    for (; first != NULL;) {
        t_list *temp = first->next;
        free(first);
        first = temp;
    }
    
    *list = NULL;
}
