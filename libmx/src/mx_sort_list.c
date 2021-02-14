#include "libmx.h"

t_list *mx_sort_list(t_list *list, bool (*compare)(void *, void *)) {
    if (!list || !compare) 
        return list;

    int size = mx_list_size(list);

    for (int i = 0; i < size; i++) {
        t_list *temp = list;

        for (int j = 0; j < size - 1; j++) {
            if (compare(temp->data, temp->next->data)) {
                void *data = temp->data; 
                temp->data = temp->next->data; 
                temp->next->data = data;     
            }

            temp = temp->next;
        }
    }

    return list;
}
