#include "ush.h"

char *mx_output_substring(char **results) {
    char *tokens = NULL;
    size_t length = 0;

    char *token = mx_str_delimiter(*results, " \t\r\n\a");

    for (; token != NULL; token = mx_str_delimiter(NULL, " \t\r\n\a")) {
        size_t len_token = strlen(token);

        if (length == 0) {
            tokens = realloc(tokens, len_token + 1);
            strcpy(tokens, token);

            length += (len_token + 1);
        }
        else {
            tokens = realloc(tokens, length + len_token + 3);

            strcat((tokens), " ");
            strcat((tokens), token);

            length += (len_token + 3);
        }
    }

    if (tokens) {
        tokens[length] = '\0';
    }

    mx_strdel(results);
    
    return tokens;
}
