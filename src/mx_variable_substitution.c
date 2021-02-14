#include "ush.h"

char *mx_variable_substitution(char *string, int *length) {
    char *result = NULL;
    int iter = 0;

    if (!string) {
        return NULL;
    }

    if (string[0] == '{') {
        iter = mx_index_char_quote(string, "}", NULL);

        if (iter < 0) {
            return NULL;
        }

        result = mx_strndup(&string[1], iter - 1);
        *length = mx_strlen(result) + 2;
    }
    else {
        for (; string[iter] && !mx_isspace(string[iter]) && (isalpha(string[iter]) || isdigit(string[iter]) || string[iter] == '?' || string[iter] =='_');) {
            iter++;
        }

        if (iter != 0) {
            result = mx_strndup(string, iter);
        }

        *length = iter;
    }
    
    return result;
}
