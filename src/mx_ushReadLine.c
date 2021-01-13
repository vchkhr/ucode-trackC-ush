#include "ush.h"
/*
 * Read line from stdin except last char ('\n').
 */
char *mx_ush_read_line(t_shell *m_s) {
    char *line = mx_strnew(1);
    char *res = NULL;
    size_t bufsize = 0;  // Have getline allocate a buffer for us

    if (getline(&line, &bufsize, stdin) < 0) {
        if (!isatty(0)) {
            m_s->exit_code = 0;
            mx_clear_all(m_s);
            exit(0);
        }
    }
    if(line[0] != '\0'){
        res = mx_strdup(line);
        mx_strdel(&line);
    }
    return res;
}
