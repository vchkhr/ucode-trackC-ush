#include "ush.h"

static t_export *create_node(void *name, void *value) {
    t_export *node =  (t_export *)malloc(sizeof(t_export));

    node->name = strdup(name);
    if(!value)
        node->value = strdup("");
    else
        node->value = strdup(value);
    node->next = NULL;
    return node;
}

void mx_push_export(t_export **list, void *name, void *value) {
    t_export *tmp;
    t_export *p;

    if (!list)
        return;
    tmp = create_node(name, value);  // Create new
    if (!tmp)
        return;
    p = *list;
    if (*list == NULL) {  // Find Null-node
        *list = tmp;
        return;
    }
    else {
        while (p->next != NULL)  // Find Null-node
            p = p->next;
        p->next = tmp;
    }
}
