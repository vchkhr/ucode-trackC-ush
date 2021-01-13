#include "ush.h"

void mx_set_variable(t_export *export, char *name, char *value) {
    int flag = 0;
    t_export *head = export;

    while (head != NULL) {
        if (strcmp(head->name, name) == 0) {
            flag++;
            free(head->value);
            head->value = strdup(value);
            break;
        }
        head = head->next;
    }
    if (!flag) {
        mx_push_export(&export, name, value);
    } 
}



