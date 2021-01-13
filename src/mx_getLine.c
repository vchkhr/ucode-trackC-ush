#include "ush.h"

static struct termios mx_disable_term(void) {
    struct termios savetty;
    struct termios tty;

    tcgetattr (0, &tty);
    savetty = tty;
    tty.c_lflag &= ~(ICANON|ECHO|ISIG|BRKINT|ICRNL
        |INPCK|ISTRIP|IXON|OPOST|IEXTEN);
    tty.c_cflag |= (CS8);
    tty.c_cc[VMIN] = 1;
    tty.c_cc[VTIME] = 0;
    tcsetattr (0, TCSAFLUSH, &tty);
    return savetty;
}

static void mx_enable_term(struct termios savetty) {
    printf("\n");
    tcsetattr (0, TCSAFLUSH, &savetty);
}

static void jynx_maze(t_shell *m_s, char *line) {
    if (m_s->history_count == m_s->history_size) {
        m_s->history_size += 1000;
        m_s->history = (char **)realloc(m_s->history, m_s->history_size);
    }
    if (strcmp(line, "") != 0) {
        m_s->history[m_s->history_count] = strdup(line);
        m_s->history_count++;
    }
}

char *mx_get_line(t_shell *m_s) {
    char *line;
    struct termios savetty;
    int out = dup(1);
    int tty = open("/dev/tty", O_WRONLY);

    dup2(tty, 1);
    mx_edit_prompt(m_s);
    savetty = mx_disable_term();
    m_s->line_len = 1024;
    mx_print_prompt(m_s);
    line = mx_get_keys(m_s);
    jynx_maze(m_s, line);
    m_s->history_index = m_s->history_count;
    mx_enable_term(savetty);
    dup2(out, 1);
    close(out);
    close(tty);
    return line;
}
