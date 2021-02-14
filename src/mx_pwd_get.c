#include "ush.h"

char *mx_pwd_get() {
    char *pwd = getenv("PWD");
    char *directory = getcwd(NULL, 256);
    char *link = realpath(pwd, NULL);

    if (link && strcmp(directory, link) == 0){
        pwd = strdup(getenv("PWD"));

        free(link);
        free(directory);
    }
    else {
        pwd = strdup(directory);

        free(directory);
    }
    
    return pwd;
}
