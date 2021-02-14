#include "ush.h"

char *mx_shlvl() {
    char *shlvl = getenv("SHLVL");

    if (!shlvl) {
        shlvl = "0";
    }

    return mx_itoa(atoi(shlvl) + 1);
}
