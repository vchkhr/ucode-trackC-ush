#include "libmx.h"

char *mx_file_to_str(const char *filename) {
    if (!filename)
        return NULL;

    int file = open(filename, O_RDONLY);

    if (file < 0) {
        close(file);
        return NULL;
    }

    int filelen = mx_filelen(filename);

    if (filelen == 0)
        return NULL;

    char *str = mx_strnew(filelen);

    read(file, str, filelen);
    close(file);

    return str;
}
