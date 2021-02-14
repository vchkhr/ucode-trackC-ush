#include "ush.h"

char *mx_slash_replace(char *string, t_echo *options) {
    char *result = (char *)malloc(mx_strlen(string) + 1);
    int length = 0;

    for (int i = 0; i <= mx_strlen(string); i++, length++) {
        if (string[i] == '\\' && string[i + 1] == '\\') {
            i++;
        }

        mx_replace_e(&i, string);

        if (string[i] == '\\' && string[i + 1] == 'c') {
            options->n = 1;

            break;
        }

        result[length] = string[i];
    }

    result[length] = '\0';
    
    return result;
}
