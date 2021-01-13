#include "ush.h"

static void backscape(int *position, char *line) {
    if (*position > 0) {
        for (int i = *position - 1; i < mx_strlen(line); i++) {
            line[i] = line[i + 1];
        }
        (*position)--;
    }
}

static void k_up(t_shell *m_s, char **line, int *position) {
    if (m_s->history[m_s->history_index - 1] && m_s->history_index > 0) {
        free(*line);
        *line = NULL;
        *line = mx_strnew(1024);
        strcpy(*line, m_s->history[m_s->history_index - 1]);
        *position = mx_strlen(*line);
        m_s->history_index--;
    }
}

static void k_down(t_shell *m_s, char **line, int *position) {
    if (m_s->history[m_s->history_index + 1] &&
        m_s->history_index < m_s->history_count) {
        free(*line);
        *line = NULL;
        *line = mx_strnew(1024);
        strcpy(*line, m_s->history[m_s->history_index + 1]);
        *position = mx_strlen(*line);
        m_s->history_index++;
    }
}

void mx_edit_command(int keycode, int *position, char **line, t_shell *m_s) {
    if (keycode == MX_K_LEFT)
        *position > 0 ? (*position)-- : 0;
    else if (keycode == MX_K_RIGHT)
        *position < mx_strlen(*line) ? (*position)++ : 0;
    else if (keycode == MX_K_END)
        *position = mx_strlen(*line);
    else if (keycode == MX_K_HOME)
        *position = 0;
    else if (keycode == MX_K_DOWN || keycode == MX_P_DOWN)
        k_down(m_s, line, position);
    else if (keycode == MX_K_UP || keycode == MX_P_UP)
        k_up(m_s, line, position);
    else if (keycode == MX_C_PROMPT) {
        m_s->prompt_status ? m_s->prompt_status-- : m_s->prompt_status++;
        mx_edit_prompt(m_s);
    }
    else if (keycode == MX_BACKSCAPE)
        backscape(position, *line);
}
