#include "ush.h"

void mx_termios_save(t_shell *m_s) {
    if (tcgetattr(STDIN_FILENO, &m_s->t_original) == -1) {
        mx_printerr("tcgetattr() failed");
        exit(MX_EXIT_FAILURE);
    }
    m_s->t_custom = m_s->t_original;
    m_s->t_custom.c_lflag &= ~(ECHO);
    m_s->t_custom.c_lflag &= ~(ICANON);
    m_s->t_custom.c_cc[VMIN] = 1;
    m_s->t_custom.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &m_s->t_custom) == -1) {
        mx_printerr("tcsetattr() failed");
        exit(MX_EXIT_FAILURE );
    }
    m_s->custom_terminal = TRUE;
}

void mx_termios_restore(t_shell *m_s) {
    if (m_s->custom_terminal == TRUE) {
        tcsetattr(STDIN_FILENO, TCSANOW, &m_s->t_original);
    }
}
