#include "ush.h"

char *mx_parent_shell(t_shell *shell, int *fd1, int *fd2, int pid) {
    size_t amount = 0;
    size_t sum_read = 0;
    char buf[BUFSIZ];
    int status;
    char *result = mx_strnew(1);

    close(fd1[0]);
    close(fd2[1]);

    for (; (amount = read(fd2[0], buf, BUFSIZ)) > 0; sum_read += amount) {
        result = realloc(result, sum_read + amount + 1);
        memcpy(&result[sum_read], buf, amount);
    }

    if (sum_read > 0) {
        if (result[sum_read - 1] == '\n') {
            result[sum_read - 1] = '\0';
        }
    }

    result[sum_read] = '\0';
    waitpid(pid, &status, 0x00000001 | 0x00000002 | 0x00000010);

    shell->exit_code = status;
    close(fd2[0]);

    return mx_output_substring(&result);
}
