#include "ush.h"

char *mx_var(t_shell *shell, char *destination) {
    for (t_export *head = shell->variables; head != NULL; head = head->next) {
        if (strcmp(head->name, destination) == 0) {
            return head->value;
        }
    }
    
    return NULL;
}
