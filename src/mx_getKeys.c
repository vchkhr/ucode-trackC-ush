#include "ush.h"

static void read_input(int *max_len, int *keycode, char *line) {
    *max_len = mx_strlen(line);
    *keycode = 0;
    read(0, keycode, 4);
}

static void add_char(int *position, char *line, int keycode, t_shell *m_s) {
    if (mx_strlen(line) >= m_s->line_len) {
        m_s->line_len += 1024;
        line = realloc(line, m_s->line_len);
    }
    for (int i = mx_strlen(line); i > *position; i--) {
        line[i] = line[i - 1];
    }
    line[*position] = keycode;
    (*position)++;
}

static void print_command(t_shell *m_s, char *line, int position, int max_len){
    for (int i = position; i <= mx_strlen(line); i++) {
        printf (" ");
    }
    for (int i = 0; i <= max_len + 2; i++) {
        printf ("\b\x1b[2K");
    }
    printf ("\r");
    mx_print_prompt(m_s);
    printf ("%s", line);
    for (int i = 0; i < mx_strlen(line) - position; i++) {
        printf ("%c[1D", 27);
    }
    fflush (NULL);
}

static void choose (int *position, char **line, int keycode, t_shell *m_s) {
    if (keycode >= 127)
        mx_edit_command(keycode, position, line, m_s);
    else if (keycode < 32)
        mx_exec_signal(keycode, line, position, m_s);
    else
        add_char(position, *line, keycode, m_s);
}

char *mx_get_keys(t_shell *m_s) {
    char *line = mx_strnew(1024);
    int keycode = 0;
    int max_len = 0;
    int position = 0;

    for (;keycode != MX_ENTER && keycode != MX_CTRL_C;) {
        mx_edit_prompt(m_s);
        read_input(&max_len, &keycode, line);
        max_len += mx_strlen(m_s->prompt);
        m_s->git ? max_len += mx_strlen(m_s->git) + 7 : 0;
        choose (&position, &line, keycode, m_s);
        if(keycode != MX_CTRL_C)
            print_command(m_s, line, position, max_len);
    }
    return line;
}
