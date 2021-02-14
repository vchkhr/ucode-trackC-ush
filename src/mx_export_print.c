#include "ush.h"

void mx_export_print(t_export *export) {
    for (t_export *head = export; head != NULL; head = head->next) {
        if (strncmp(head->name,"BASH_FUNC_", 10) != 0) {
            printf("export %s", head->name);

            if (head->value) {
                printf("=\"%s\"", head->value);
            }
            
            printf("\n");
        }
    }
}
