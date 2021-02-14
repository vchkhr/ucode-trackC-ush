#include "ush.h"

t_export *mx_create_node_export(void *name, void *value) {
    t_export *node = (t_export *)malloc(sizeof(t_export));

    node->name = strdup(name);

    if (!value) {
        node->value = strdup("");
    }
    else {
        node->value = strdup(value);
    }

    node->next = NULL;
    
    return node;
}
