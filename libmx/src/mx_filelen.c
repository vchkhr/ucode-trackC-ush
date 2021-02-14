#include "libmx.h"

int mx_filelen(const char *filename) {
    if (!filename)
        return 0;
    
    int file = open(filename, O_RDONLY);

    if (file < 0) {
        close(file);
        return 0;
    }

    int len = 0;
    char buf;

    while (read(file, &buf, 1))
        len++;

    return len;
}
