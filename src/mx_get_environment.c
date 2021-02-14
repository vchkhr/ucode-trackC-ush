#include "ush.h"

char **mx_get_environment(t_export *environment) {
    char **environment_array = (char **)malloc(sizeof(char *) * 1024);
    t_export *head = environment;
    int i = 0;

    for (; head != NULL; i++) {
        char *temp;
        char *line;

        line = NULL;
        temp = mx_strjoin(head->name, "=");
        line = mx_strjoin(temp, head->value);
        free(temp);
        environment_array[i] = strdup(line);
        free(line);
        head = head->next;
    }
    
    environment_array[i] = NULL;
    return environment_array;
}
