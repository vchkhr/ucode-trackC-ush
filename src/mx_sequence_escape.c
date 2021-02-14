#include "ush.h"

void mx_sequence_escape(t_process *process, int i, t_echo options) {
    char *temp = mx_slash_replace(process->arguments_amount[i], &options);
    char *sequences[] = {"\\a", "\\b", "\\f", "\\n", "\\r", "\\t", "\\v", NULL};
    char *escape[] = {"\a", "\b", "\f", "\n", "\r", "\t", "\v", NULL};

    free(process->arguments_amount[i]);
    process->arguments_amount[i] = strdup(temp);
    free(temp);

    for (int j = 0; sequences[j] != NULL; j++) {
        if (strstr(process->arguments_amount[i],sequences[j])) {
            temp = mx_substr_replace_echo(process->arguments_amount[i],sequences[j], escape[j]);
            free(process->arguments_amount[i]);
            
            process->arguments_amount[i] = strdup(temp);
            free(temp);
        }
    }
}
