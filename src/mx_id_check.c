#include "ush.h"

int mx_id_check(char *argument) {
    int flag = 0;

    for (int j = 0; mx_strlen(argument) > j; j++) {
        if (!isalpha(argument[j]) && !isdigit(argument[j]) && argument[j] != '_') {
            flag++;
        }
    }

    return flag;
}
