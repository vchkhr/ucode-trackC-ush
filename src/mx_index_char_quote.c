#include "ush.h"

int mx_index_char_quote(char *s, char *c, char *q) {
    if (!s || !c) {
        return -2;
    }

    for (int i = 0; s[i]; i++) {
        if (s[i] == '\\') {
            i++;
        }
        else if (mx_isdelim(s[i], q) && !mx_strncmp(&s[i], "$(", 2)) {
            for (; s[i] && s[i] != ')';) {
                if (s[i] == '\\') {
                    i += 2;
                }
                else {
                    i++;
                }
            }
        }
        else if (mx_isdelim(s[i], q) && !mx_strncmp(&s[i], "() {", 4)) {
            for (; s[i] && s[i] != '}';) {
                if (s[i] == '\\') {
                    i += 2;
                }
                else {
                    i++;
                }
            }
        }
        else if (mx_isdelim(s[i], q) && mx_isdelim(s[i], "`\'\"")) {
            mx_char_quote(s, &i, q);
        }
        else {
            for (int j = 0; j < mx_strlen(c); j++) {
                if (s[i] == c[j]) {
                    return i;
                }
            }
        }
    }
    
    return -1;
}
