#include "ush.h"

static char *get_variable(t_shell *m_s, char *target) {
    t_export *head = m_s->variables;

    while (head != NULL) {
        if (strcmp(head->name, target) == 0) {
            return head->value;
        }
        head = head->next;
    }
    return NULL;
}

static void customize(t_shell *m_s) {
    char *info = NULL;
    int count = 0;
    char **arr = NULL;

    if (strcmp(m_s->pwd, "/") == 0)
        info = strdup("/");
    else if (getenv("HOME") && strcmp(m_s->pwd, getenv("HOME")) == 0)
        info = strdup("~");
    else {
        arr = mx_strsplit(m_s->pwd, '/');
        count = 0;
        while (arr[count] != NULL)
            count++;
        info = strdup(arr[count - 1]);
        mx_del_strarr(&arr);
    }
    m_s->prompt = strdup(info);
    free(info);
}

void mx_print_prompt(t_shell *m_s) {
    if (!m_s->prompt_status)
        printf("%s", MX_BOLD_MAGENTA);
    printf ("%s", m_s->prompt);
    if (!m_s->prompt_status && m_s->git)
        printf(" %sgit:(%s%s%s)", MX_BOLD_BLUE, MX_RED,
               m_s->git, MX_BOLD_BLUE);
    if (!m_s->prompt_status)
        printf("%s", MX_RESET);
    printf ("> ");
    fflush (NULL);
}

void mx_edit_prompt(t_shell *m_s) {
    if (m_s->prompt)
        free(m_s->prompt);
    if (!m_s->prompt_status)
        customize(m_s);
    else {
        if (get_variable(m_s, "PROMPT"))
            m_s->prompt = strdup(get_variable(m_s, "PROMPT"));
        else
            m_s->prompt = strdup("u$h");
    }
}
