#include "ush.h"

bool mx_unmatched_error(char character) {
    if (character == '\"' || character == '\'') {
        mx_printerr("Odd number of quotes.\n");

        return true;
    }
    else {
        mx_printerr("Unmatched ");

        write(2, &character, 1);

        mx_printerr(".\n");
        
        return true;
    }
}
