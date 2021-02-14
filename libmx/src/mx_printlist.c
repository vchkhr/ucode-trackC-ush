#include "libmx.h"

void mx_printlist(t_list *list) {
    if (!list)
        return;
    
    t_list *cpy = list;

    while (cpy) {
        mx_printchar('(');
        mx_printstr(cpy->data);
        mx_printchar(')');

        cpy = cpy->next;

        cpy ? mx_printstr(" --> ") : mx_printchar('\n');
    }
}
