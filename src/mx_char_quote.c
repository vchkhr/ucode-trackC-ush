#include "ush.h"

void mx_char_quote(char *string, int *ii, char *queue) {
    int i = *ii;

    if ((mx_isdelim(string[i], queue) && string[i] == '`') || (mx_isdelim(string[i], queue) && string[i] == '\"')) {
        char temp = string[i];
        i++;

        for (; string[i] && string[i] != temp;) {
            if (string[i] == '\\') {
                i += 2;
            }
            else {
                i++;
            }
        }
    }
    else if (mx_isdelim(string[i], queue) && string[i] == '\'') {
        for (i++; string[i] && string[i] != '\'';) {
            i++;
        }
    }

    *ii = i;
}
