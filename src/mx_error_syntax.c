#include "ush.h"

char *mx_error_syntax(char *string) {
    mx_printerr("ush: syntax error near unexpected token `");
    mx_printerr(string);
    mx_printerr("'\n");
    
    return NULL;
}
