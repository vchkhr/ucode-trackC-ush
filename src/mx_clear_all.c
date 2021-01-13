#include "ush.h"

void mx_clear_all(t_shell *m_s) {
    mx_clear_export(m_s->exported);
    mx_clear_export(m_s->variables);
    mx_clear_export(m_s->functions);
    mx_clear_export(m_s->aliases);
    mx_del_strarr(&m_s->history);
    free(m_s->kernal);
    free(m_s->pwd);
}

void mx_clear_export(t_export *list) {
    t_export *q = list;
    t_export *tmp = NULL;

    if (!(list) || !list)
        return;
    while (q) {
        if (q->name)
            free(q->name);
        if (q->value)
            free(q->value);
        tmp = q->next;
        free(q);
        q = tmp;
    }
    list = NULL;
}
