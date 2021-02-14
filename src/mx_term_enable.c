#include "ush.h"

void mx_term_enable(struct termios safe) {
    printf("\n");

    tcsetattr(0, TCSAFLUSH, &safe);
}
