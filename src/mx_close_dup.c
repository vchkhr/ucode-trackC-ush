#include "ush.h"

void mx_close_dup(int inp, int out) {
    if (inp != out) {
        dup2(inp, out);
        close(inp);
    }
}
