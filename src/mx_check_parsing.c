#include "ush.h"

bool mx_check_parsing(char *string, int n) {
    int index = mx_index_char_quote(&string[n + 1], ";|&><", "\"\'`$(");

    if (index == 0) {
        if (string[n] != string[n + 1] || string[n + 1] == ';') {
            return mx_error_parse(&string[n + 1], 1);
        }
        else if (string[n + 2]) {
            int temp = mx_index_char_quote(&string[n + 2], ";|&><", "\"\'`$(");

            if (temp == 0) {
                return mx_error_parse(&string[n + 2], 1);
            }
        }
    }
    
    return false;
}
