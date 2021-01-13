#include "ush.h"

void mx_sig_h(int signal) {
    if (signal == SIGPIPE)
        mx_printerr("err write PIPE!!!!\n");
}
