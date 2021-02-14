#include "ush.h"

void mx_environment_print(t_export *environments) {
    for (t_export *head = environments; head != NULL; head = head->next) {
        printf("%s=%s\n", head->name, head->value);
    }
}
