#include "ush.h"

char **mx_tokens_create(char **tokens, int *buffer_size) {
    if (tokens == NULL) {
        tokens = malloc((*buffer_size) * sizeof(char*));

        if (!tokens) {
            mx_printerr_red("ush: allocation error\n");

            return NULL;
        }
    }
    else {
        (*buffer_size) += 64;
        tokens = realloc(tokens, (*buffer_size) * sizeof(char*));

        if (!tokens) {
            mx_printerr_red("ush: allocation error\n");

            return NULL;
        }
    }
    
    return tokens;
}
