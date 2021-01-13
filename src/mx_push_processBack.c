#include "ush.h"

static t_process *init_process(t_ast *list) {
    t_process *p = (t_process *)malloc(sizeof(t_process));

    if (!p)
        return NULL;
    p->argv = mx_strdup_arr(list->args);
    p->delim = list->type;
    p->command = mx_strdup(list->args[0]);
    p->input_path = NULL;
    p->output_path = NULL;
    p->redir_delim = 0;
    p->redirect = NULL;
    p->foregrd = 1;
    p->pipe = 0;
    p->r_infile = (int *) malloc(sizeof(int) * 1);
    p->r_outfile = (int *) malloc(sizeof(int) * 1);
    if (p->delim == FON)
        p->foregrd = 0;
    else if (p->delim == PIPE)
        p->pipe = 1;
    p->next = NULL;
    return p;
}

static t_process *create_process(t_shell *m_s, t_ast *list) {
    t_process *p;
    t_ast *t = list->left;
    int index = 0;

    if (!(p = init_process(list)))
        return NULL;
    if (list->left && (t->args = mx_filters(t->token, m_s)) && *(t->args)) {
        p->redir_delim = t->type;
        if (MX_IS_REDIR_INP(t->type))
            p->input_path = mx_strdup(t->args[0]);
        else if (MX_IS_REDIR_OUTP(t->type))
            p->output_path = mx_strdup(t->args[0]);
        for (t_ast *q = list->left; q; q = q->next)
            if (q->args
                || ((q->args = mx_filters(q->token, m_s)) && *(q->args)))
                mx_redir_push_back(&p->redirect, q->args[0], q->type);
    }



    if ((index = mx_builtin_commands_idex(m_s, p->argv[0])) == -1)
        p->type = -1;
    else
        p->type = index;
    return p;
}

void mx_push_process_back(t_process **process,
                                 t_shell *m_s, t_ast *list) {
    t_process *tmp;
    t_process *p;

    if (!process || !m_s || !list)
        return;
    tmp = create_process(m_s, list);
    if (!tmp)
        return;
    p = *process;
    if (*process == NULL) {
        *process = tmp;
        return;
    }
    else {
        while (p->next != NULL)
            p = p->next;
        p->next = tmp;
    }
}

void mx_clear_process(t_process *p) {
    if (!p)
        return;
    mx_del_strarr(&p->argv);
    mx_strdel(&p->command);
    mx_strdel(&p->input_path);
    mx_strdel(&p->output_path);
    mx_redir_clear_list(&p->redirect);
    if (p->r_infile)
        free(p->r_infile);
    if (p->r_outfile)
        free(p->r_outfile);
    free(p);
}
