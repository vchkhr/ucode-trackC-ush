#include "ush.h"

char *mx_delimiter_error_print(int type) {
    if (type == 0) {
        return mx_strdup(";");
    }
    else if (type == 1) {
        return mx_strdup("&");
    }
    else if (type == 2) {
        return mx_strdup("&&");
    }
    else if (type == 3) {
        return mx_strdup("||");
    }
    else if (type == 4) {
        return mx_strdup("|");
    }
    else if (type == 5) {
        return mx_strdup("<");
    }
    else if (type == 6) {
        return mx_strdup("<<");
    }
    else if (type == 7) {
        return mx_strdup(">");
    }
    else if (type == 8) {
        return mx_strdup(">>");
    }

    return NULL;
}
