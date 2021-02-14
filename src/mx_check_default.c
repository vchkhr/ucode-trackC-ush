#include "ush.h"

void mx_check_default (char **list, char *command, t_list **output, int *flag) {
    for (int j = 0; list[j] != NULL; j++) {
        if (strcmp(list[j], command) == 0) {
            char *str = mx_strjoin(command, ": ush built-in command");
            
            mx_push_back(&*output, str);
            free(str);
            (*flag)++;
        }
    }
}
