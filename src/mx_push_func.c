#include "ush.h"

void mx_push_func(t_ast **result, char *argument, int type, t_shell *shell) {
    t_export *queue;
    char *temp = mx_strdup(argument);
    char *arg = mx_str_delimiter(temp, " \t\r\n\a");

    for (queue = shell->functions; queue; queue = queue->next) {
        if (mx_strcmp(arg, queue->name) == 0 && !mx_strstr(queue->value, arg)) {
            mx_strdel(&temp);
            *result = mx_all_commands(*result, queue->value, shell, type);

            return;
        }
    }
    for (queue = shell->aliases; queue; queue = queue->next) {
        if (mx_strcmp(arg, queue->name) == 0 && !mx_strstr(queue->value, arg)) {
            mx_strdel(&temp);
            *result = mx_all_commands(*result, queue->value, shell, type);
            return;
        }
    }
    
    mx_strdel(&temp);
    mx_append(result, argument, type);
}
