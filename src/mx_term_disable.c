#include "ush.h"

struct termios mx_term_disable() {
    struct termios safe;
    struct termios temp;

    tcgetattr (0, &temp);

    safe = temp;

    temp.c_lflag &= ~(ICANON|ECHO|ISIG|BRKINT|ICRNL|INPCK|ISTRIP|IXON|OPOST|IEXTEN);
    temp.c_cflag |= (CS8);
    temp.c_cc[VMIN] = 1;
    temp.c_cc[VTIME] = 0;

    tcsetattr(0, TCSAFLUSH, &temp);
    
    return safe;
}
