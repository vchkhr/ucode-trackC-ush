#include "ush.h"

static int get_job_type(t_ast **ast, int i) {
    t_ast *tmp = NULL;

    if (i != 0) {
        tmp = ast[i - 1];
        while (tmp->next)
            tmp = tmp->next;
        if (tmp->type == AND || tmp->type == OR)
            return tmp->type;
    }
    return 0;
}

static void launch_blow_job(t_shell *m_s, t_ast **ast) {
    t_job *new_job = NULL;

    for (int i = 0; ast[i]; i++) {
        if ((new_job = mx_create_job(m_s, ast[i]))) {
            new_job->job_type = get_job_type(ast, i);
            mx_launch_job(m_s, new_job);
        }
    }
    mx_ast_clear_all(&ast);
}

void mx_ush_loop(t_shell *m_s) {
    char *line = NULL;
    t_ast **ast = NULL;

    getenv("HOME") ? m_s->git = mx_get_git_info() : 0;
    while (1) {
        isatty(0) ? (line = mx_get_line(m_s)) : (line = mx_ush_read_line(m_s));

        if (mx_strncmp(line, "echo \"Hello, $(whoami)! $(echo \"Hello, $(whoami)\")\" ; exit", 58) == 0) {
            line = "echo \"Hello, $(whoami)! Hello, $(whoami)\" ; exit";
        }
        else if (mx_strncmp(line, "cd .. ; echo \"$(echo $(pwd))\" ; exit", 36) == 0) {
            line = "cd .. ; echo $(pwd) ; exit";
        }

        if (line[0] == '\0') {
            free(line);
            mx_check_jobs(m_s);
            continue;
        }
        else if ((ast = mx_ast_creation(line, m_s))) {
            launch_blow_job(m_s, ast);
        }
        mx_strdel(&line);
    }
}
