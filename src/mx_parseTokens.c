#include "ush.h"

static char **create_tokens(char **tokens, int *bufsize) {
    if (tokens == NULL) {
        tokens = malloc((*bufsize) * sizeof(char*));
        if (!tokens) {
            mx_printerr_red("ush: allocation error\n");
            return NULL;
        }
    }
    else {
        (*bufsize) += 64;
        tokens = realloc(tokens, (*bufsize) * sizeof(char*));
        if (!tokens) {
            mx_printerr_red("ush: allocation error\n");
            return NULL;
        }
    }
    return tokens;
}

char **mx_parce_tokens(char *line) {
    int position = 0;
    int bufsize = 64;
    char **tokens = NULL;
    char *token;

    tokens = create_tokens(tokens, &bufsize);  // Malloc
    token = mx_strtok(line, MX_USH_TOK_DELIM);
    while (token != NULL) {
        tokens[position] = token;
        position++;
        if (position >= bufsize)
            tokens = create_tokens(tokens, &bufsize);  // Realloc
        token = mx_strtok(NULL, MX_USH_TOK_DELIM);
    }
    tokens[position] = NULL;
    return tokens;
}
