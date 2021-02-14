#include "ush.h"

int mx_job_type(t_ast **ast, int i) {
    t_ast *temp = NULL;

    if (i != 0) {
        for (temp = ast[i - 1]; temp->next;) {
            temp = temp->next;
        }

        if (temp->type == 2 || temp->type == 3) {
            return temp->type;
        }
    }
    
    return 0;
}
