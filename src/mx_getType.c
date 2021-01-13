#include "ush.h"

char mx_get_type(struct stat file_stat) {
    char result = '-';

    if ((file_stat.st_mode & S_IFMT) == S_IFCHR)
        return 'c';
    if ((file_stat.st_mode & S_IFMT) == S_IFBLK)
        return 'b';
    if ((file_stat.st_mode & S_IFMT) == S_IFIFO)
        return 'p';
    if ((file_stat.st_mode & S_IFMT) == S_IFSOCK)
        return 's';
    if ((file_stat.st_mode & S_IFMT) == S_IFLNK)
        return 'l';
    if ((file_stat.st_mode & S_IFMT) == S_IFDIR)
        return 'd';
    return result;
}
