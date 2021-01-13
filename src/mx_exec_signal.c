#include "ush.h"

static void exit_ush(t_shell *m_s)
{
    printf("exit\n");
    mx_clear_all(m_s);
    exit(EXIT_SUCCESS);
}

static void reverse_backscape(int *position, char *line)
{
    for (int i = *position; i < mx_strlen(line); i++)
    {
        line[i] = line[i + 1];
    }
}

void mx_exec_signal(int keycode, char **line, int *position, t_shell *m_s)
{
    if (keycode == MX_CTRL_C)
    {
        for (int i = 0; i < mx_strlen(*line); i++)
        {
            *line[i] = '\0';
        }
    }
    if (keycode == MX_CTRL_D)
        if (strcmp(*line, "") == 0)
        {
            exit_ush(m_s);
        }
        else
        {
            reverse_backscape(position, *line);
        }
    else if (keycode == MX_TAB)
    {
        if (mx_strlen(*line) == 0) {
            return;
        }

        static DIR *dir = NULL;
        static struct dirent *entry = NULL;
        static int temp_position = 0;
        static int length_tab_word = 0;

        if (*position < temp_position) {
            if (mx_strlen(*line) == 0 || !mx_isspace((*line)[*position - 1])) {
            return;
            }
            temp_position = *position;
            length_tab_word = 0;
        }

        if (dir == NULL)  {
            dir = opendir(".");
        }
 
        if (dir == NULL) {
            return;
        }

        if (temp_position == 0 || *position > temp_position + length_tab_word) {
            temp_position = *position;
            closedir(dir);
            dir = opendir(".");
        }

        while ((entry = readdir(dir)) != NULL)
        {

            if (entry->d_name[0] != '.')
            {
                for (int i = temp_position; i <= *position; i++) {
                    (*line)[i] = '\0';
                }
                *position = temp_position;
                length_tab_word = mx_strlen(entry->d_name);
                for (int i = 0; i < length_tab_word; i++) {
                    (*line)[(*position)++] = entry->d_name[i];
                }

                return;
            }
        }

        closedir(dir);
        dir = NULL;

    }
}
