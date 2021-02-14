#include "ush.h"

bool mx_quotes_check(char *string) {
    for (int i = 0; string[i]; i++) {
        if (string[i] == '\\') {
            i++;
        }
        else if (mx_isdelim(string[i], "`\"(){")) {
            char temp = mx_check_quote(string, &i);

            if (temp && !string[i]) {
                return mx_unmatched_error(temp);
            }
        }
        else if (string[i] == '\'') {
            for (i++; string[i] && string[i] != '\'';) {
                i++;
            }

            if (!string[i]) {
                return mx_unmatched_error('\'');
            }
        }
    }

    return false;
}
