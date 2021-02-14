#include "ush.h"

void mx_left_print(t_ast *queue) {
    for (t_ast *result = queue->previous; result; result = result->next) {
        mx_printstr("redir == ");

        if (result->type == 5) {
            mx_printstr("< ");
        }
        else if (result->type == 6) {
            mx_printstr("<< ");
        }
        else if (result->type == 7) {
            mx_printstr("> ");
        }
        else if (result->type == 8) {
            mx_printstr(">> ");
        }
        
        if (result->arguments) {
            mx_print_strarr_in_line(result->arguments, " ");
        }
        else if (result->token) {
            mx_printstr(queue->token);
            mx_printstr("\n");
        }
    }
}
