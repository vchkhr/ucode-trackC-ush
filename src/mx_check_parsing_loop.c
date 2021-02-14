#include "ush.h"

bool mx_check_parsing_loop(char *string) {
    for (int i = 0; string;) {
        if ((i = mx_index_char_quote(string, ";|&><", "\"\'`$(")) >= 0) {
            if ((string[i + 1] == '\0' && string[i] != ';' && string[i] != '&') || mx_strcmp(&string[i], "&&") == 0) {
                return mx_error_parse("\\n", 2);
            }
            if (string[i + 1] && mx_check_parsing(string, i)) {
                return true;
            }
            
            string += i + 1;
        }
        else {
            break;
        }
    }
    
    return false;
}
