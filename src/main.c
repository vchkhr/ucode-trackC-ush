#include "ush.h"

int main(int argc, char **argv) {
    t_shell *m_s = mx_init_shell(argc, argv);

    (void)argc;
    (void)argv;
    mx_ush_loop(m_s);
    return MX_EXIT_SUCCESS;
}
