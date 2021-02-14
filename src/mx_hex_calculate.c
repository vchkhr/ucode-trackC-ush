#include "ush.h"

char *mx_hex_calculate(unsigned long nbr, int length) {
    char *string = NULL;

    string = mx_strnew(length);

    for (int i = 0; i < length; i++) {
        int ost = nbr % 16;
        nbr = nbr / 16;

        if (ost >= 0 && ost <= 9) {
            ost += 48;
        }
        if (ost >= 10 && ost <= 15) {
            ost += 87;
        }

        string[i] = ost;
    }

    mx_str_reverse(string);
    
    return string;
}
