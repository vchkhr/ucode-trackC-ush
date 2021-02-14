#include "ush.h"

char mx_check_quote(char *string, int *i) {
    int j = *i;
    char temp;

    if (string[j] == '(' && string[j - 1] && string[j - 1] == '$') {
        temp = ')';
    }
    else if (string[j] == '{' && string[j - 3] && !mx_strncmp(&string[j - 3], "() ", 3)) {
        temp = '}';
    }
    else if (string[j] == '(' || string[j] == ')' || string[j] == '{') {
        return 0;
    }
    else {
        temp = string[j];
    }

    for (j++; string[j] && string[j] != temp; j++) {
        if (string[j] == '\\') {
            j++;
        }
    }

    *i = j;

    if (temp == ')') {
        temp = '(';
    }
    
    return temp;
}
