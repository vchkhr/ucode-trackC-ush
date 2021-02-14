#include "ush.h"

void mx_signal_execution(int key, char **string, int *position, t_shell *shell) {
    if (key == 3) {
        for (int i = 0; i < mx_strlen(*string); i++) {
            *string[i] = '\0';
        }
    }
    if (key == 4) {
        if (strcmp(*string, "") == 0) {
            mx_ush_exit(shell);
        }
        else {
            mx_backspace_reverse(position, *string);
        }
    }
    else if (key == 9) {
        if (mx_strlen(*string) == 0) {
            return;
        }

        static DIR *directory = NULL;
        static struct dirent *entry = NULL;
        static int pos = 0;
        static int length = 0;

        if (*position < pos) {
            if (mx_strlen(*string) == 0 || !mx_isspace((*string)[*position - 1])) {
                return;
            }

            pos = *position;
            length = 0;
        }

        if (directory == NULL)  {
            directory = opendir(".");
            
            return;
        }

        if (pos == 0 || *position > pos + length) {
            pos = *position;
            closedir(directory);
            directory = opendir(".");
        }

        for (; (entry = readdir(directory)) != NULL;) {
            if (entry->d_name[0] != '.') {
                for (int i = pos; i <= *position; i++) {
                    (*string)[i] = '\0';
                }

                *position = pos;
                length = mx_strlen(entry->d_name);

                for (int i = 0; i < length; i++) {
                    (*string)[(*position)++] = entry->d_name[i];
                }

                return;
            }
        }

        closedir(directory);
        directory = NULL;
    }
}
