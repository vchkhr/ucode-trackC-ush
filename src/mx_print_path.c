#include "ush.h"

void mx_print_path(t_list *output, int flag, char *command, t_which options) {
    if (!flag) {
        mx_printerr(command);
        mx_printerr(" not found\n");

        return;
    }
    
    for (t_list *head = output; head; head = head->next) {
        char error[] = "built-in command";
        char *array = &((char*)(head->data))[strlen(head->data) - 16];

        if (strcmp(error, array) == 0) {
            mx_printerr(head->data);
            mx_printerr("\n");

            if (!options.a) {
                break;
            }

            head = head->next;

            continue;
        }

        printf("%s\n", head->data);

        if (!options.a) {
            break;
        }
    }
}
