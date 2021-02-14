#include "ush.h"

void mx_info_command(t_shell *shell, char *command, int *flag, t_which options) {
    char *path = getenv("PATH");

    if (!path) {
        path = "";
    }

    char **array = NULL;

	array = mx_strsplit(path, ':');
	*flag = 0;

    t_list *output= NULL;
    
	mx_check_default(shell->default_list, command, &output, flag);
    mx_path_check_command_info(array, command, &output, flag);
    mx_del_strarr(&array);

    mx_print_path(output, *flag, command, options);
    mx_clear_list(&output);
}
