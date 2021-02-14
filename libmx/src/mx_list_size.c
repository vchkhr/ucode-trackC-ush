#include "libmx.h"

int mx_list_size(t_list *list) {
    if (!list)
        return 0;

    int counter = 1;
    t_list *cpy = list;

    while (cpy->next) {
        cpy = cpy->next;
        counter++;
    }

    return counter;
}
