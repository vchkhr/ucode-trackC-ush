#include "ush.h"

void mx_trim_quote_help(char *string, char *temp, int *ii, int *jj) {
    int i = *ii;
    int j = *jj;

    if (string[i] == '\"') {
        for (i++; string[i] && string[i] != '\"'; i++, j++) {
            if (string[i] == '\\' && mx_isdelim(string[i + 1], "$`\"\\!")) {
                i++;
            }

            temp[j] = string[i];
        }

        j--;
    }
    else if (string[i] == '\'') {
        for (i++; string[i] && string[i] != '\''; i++, j++) {
            temp[j] = string[i];
        }

        j--;
    }
    
    *ii = i;
    *jj = j;
}
