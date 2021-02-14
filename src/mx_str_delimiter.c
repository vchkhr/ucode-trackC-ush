#include "ush.h"

char *mx_str_delimiter(char *string, const char *delimiter) {
    static char *old;

    return mx_string_delimiter(string, delimiter, &old);
}
