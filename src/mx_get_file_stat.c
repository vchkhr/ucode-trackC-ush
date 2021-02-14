#include "ush.h"

char mx_get_file_stat(struct stat file) {
    char result = '-';

    if ((file.st_mode & S_IFMT) == S_IFCHR) {
        return 'c';
    }
    if ((file.st_mode & S_IFMT) == S_IFBLK) {
        return 'b';
    }
    if ((file.st_mode & S_IFMT) == S_IFIFO) {
        return 'p';
    }
    if ((file.st_mode & S_IFMT) == S_IFSOCK) {
        return 's';
    }
    if ((file.st_mode & S_IFMT) == S_IFLNK) {
        return 'l';
    }
    if ((file.st_mode & S_IFMT) == S_IFDIR) {
        return 'd';
    }
    
    return result;
}
