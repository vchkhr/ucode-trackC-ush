#include "ush.h"

char *mx_get_quotes(char *string, const char *delimiter, char *end) {
    for (; *string && !(mx_isdelim(*string, (char *)delimiter));) {
        if (*string == '\\') {
            string += 2;
        }
        else if (*string == '\'') {
            string += mx_get_char_index(string + 1, '\'') + 2;
        }
        else if (mx_isdelim(*string, "\"")) {
            string += mx_index_char_quote(string + 1, "\"", "`$") + 2;
        }
        else if (mx_isdelim(*string, "`")) {
            string += mx_index_char_quote(string + 1, "`", "\"\'$(") + 2;
        }
        else if (mx_strncmp(string, "$(", 2) == 0) {
            string += mx_index_char_quote(string + 2, ")", "\"\'`$(") + 3;
        }
        else if (mx_strncmp(string, "() {", 4) == 0) {
            string += mx_index_char_quote(string + 4, "}", "\"\'`$(") + 5;
        }
        else {
            string++;
        }
    }

    end = string;

    return end;
}
