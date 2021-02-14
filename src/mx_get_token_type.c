#include "ush.h"

int mx_get_token_type(char *delim) {
    if (!mx_strcmp(delim, ";")) {
        return 0;
    }
    else if (!mx_strcmp(delim, "&")) {
        return 1;
    }
    else if (!mx_strcmp(delim, "&&")) {
        return 2;
    }
    else if (!mx_strcmp(delim, "||")) {
        return 3;
    }
    else if (!mx_strcmp(delim, "|")) {
        return 4;
    }
    else if (!mx_strcmp(delim, "<")) {
        return 5;
    }
    else if (!mx_strcmp(delim, ">")) {
        return 6;
    }
    else if (!mx_strcmp(delim, ">")) {
        return 7;
    }
    else if (!mx_strcmp(delim, ">>")) {
        return 8;
    }
    
    return 9;
}
