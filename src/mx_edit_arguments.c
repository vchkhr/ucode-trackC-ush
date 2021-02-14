#include "ush.h"

void mx_edit_arguments(int amount, t_process *process) {
    t_echo options = {0, 0, 0};

    mx_options_fill_echo(process->arguments_amount, &options, amount);

    for (int i = amount + 1; process->arguments_amount[i] != NULL; i++) {
        if (!options.E && strstr(process->arguments_amount[i], "\\")) {
            mx_sequence_escape(process, i, options);
        }

        printf("%s",process->arguments_amount[i]);

        if (strstr(process->arguments_amount[i],"\\c")) {
            break;
        }
        
        if (process->arguments_amount[i + 1]) {
            mx_printstr(" ");
        }
    }

    if (!options.n) {
        printf("\n");
    }
}
