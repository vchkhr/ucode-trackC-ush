#include "ush.h"

char *mx_string_delimiter(char *string, const char *delimiter, char **arrays) {
    if (string == NULL) {
        string = *arrays;
    }

    string += strspn(string, delimiter);

    if (*string == '\0') {
        *arrays = string;

        return NULL;
    }

    char *end = NULL;

    if (!(end = mx_get_quotes(string, delimiter, end))) {
        return NULL;
    }
    if (*end == '\0') {
        *arrays = end;

        return string;
    }

    *end = '\0';
    *arrays = end + 1;

    return string;
}
