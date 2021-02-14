#include "ush.h"

char **mx_tokens_parse(char *string) {
    int position = 0;
    int buffer_size = 64;
    char **tokens = NULL;
    char *token;

    tokens = mx_tokens_create(tokens, &buffer_size);
    token = mx_str_delimiter(string, " \t\r\n\a");

    for (; token != NULL; token = mx_str_delimiter(NULL, " \t\r\n\a")) {
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
            tokens = mx_tokens_create(tokens, &buffer_size);
        }
    }

    tokens[position] = NULL;
    
    return tokens;
}
