#include "ush.h"

char *mx_nbr_to_hex(unsigned long nbr) {
    char *string = NULL;

    if (nbr == 0) {
        string = mx_strnew(2);
        *string = '0';

        return string;
    }

    int length = 0;

    for (unsigned long number = nbr; number != 0; length++) {
        number = number / 16;
    }

    return mx_hex_calculate(nbr, length);
}
