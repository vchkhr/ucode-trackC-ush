#include "ush.h"

bool mx_check_errors_parsing(char *string) {
    if (!string || mx_quotes_check(string) || mx_check_parsing_loop(string)) {
        return true;
    }
    if (string[0] && mx_isdelim(string[0], "|&><")) {
        if (string[1] && mx_isdelim(string[1], "|&><")) {
            return mx_error_parse(&string[0], 2);
        }
        else {
            return mx_error_parse(&string[0], 1);
        }
    }

    return false;
}
