#include "libmx.h"

unsigned long mx_pow_rec(int n, int pow) {
    unsigned long res = 0;
    if (pow  >= 0) {
        if(pow == 0) {
            return 1;;
        }
        res = n;
        res *= mx_pow_rec(n, pow - 1);
    }
    return res;
}
