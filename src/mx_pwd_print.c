#include "ush.h"

void mx_pwd_print(char *directory, int *result, t_shell *shell, t_pwd options) {
    *result = 0;
    
    if (options.p < 0) {
        printf("%s\n", shell->pwd);
    }
    else {
        printf("%s\n", directory);
    }

    free(directory);
}
