#include "ush.h"

void mx_trim_quote(char **strings) {
    char *temp = NULL;

    for (int k = 0; strings[k]; k++) {
        char *s = strings[k];

        temp = mx_strnew(mx_strlen(s));

        for (int i = 0, j = 0; s[i]; i++, j++) {
            if (s[i] && s[i] == '\\') {
                i++;
                temp[j] = s[i];
            }
            else if (s[i] && (s[i] == '\"' || s[i] == '\'')) {
                mx_trim_quote_help(s, temp, &i, &j);
            }
            else {
                temp[j] = s[i];
            }
        }
        
        mx_strdel(&strings[k]);

        strings[k] = temp;
    }
}
