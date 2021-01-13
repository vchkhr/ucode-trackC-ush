#include "ush.h"

static void check_path(char **arr, char *command, t_list **output,
                       int *flag) {
    int i = 0;
    char *name = NULL;
    DIR *dptr;
    struct dirent *ds;

    while (arr[i] != NULL) {
        dptr = opendir(arr[i]);
        if (dptr != NULL) {
            while ((ds = readdir(dptr)) != 0) {
                if (strcmp(ds->d_name, command) == 0 && command[0] != '.') {
                    name = strcat(arr[i], "/");
                    name = strcat(name, command);
                    mx_push_back(&*output, name);
                    (*flag)++;
                }
            }
            closedir(dptr);
        }
        i++;
    }
}

static void check_builtin (char **list, char *command, t_list **output,
                           int *flag) {
    for (int j = 0; list[j] != NULL; j++) {
        if (strcmp(list[j], command) == 0) {
            char *str = mx_strjoin(command, ": ush built-in command");
            mx_push_back(&*output, str);
            free(str);
            (*flag)++;
        }
    }
}

static void print_path(t_list *output, int flag, char *command, which_t which_options) {
    if (!flag){
        mx_printerr(command);
        mx_printerr(" not found\n");
    }
    else {
        t_list *head = output;

        while (head) {
            //STOP TRYING TO UNDERSTAND THIS CODE!!!
            char arr[] = "built-in command";
            char *arr1 = &((char*)(head->data))[strlen(head->data) - 16];
            if (strcmp(arr, arr1) == 0) {
                mx_printerr(head->data);
                mx_printerr("\n");

                if (!which_options.a)
                    break;
                head = head->next;

                continue;
            }
            //

            printf("%s\n", head->data);
            if (!which_options.a)
                break;
            head = head->next;
        }
    }
}

static void mx_clear_list(t_list **list) {
    t_list *q = *list;
    t_list *tmp = NULL;

    if (!(*list) || !list)
        return;
    while (q) {
         mx_strdel((char **)&q->data);
        tmp = q->next;
        free(q);
        q = tmp;
    }
    *list = NULL;
}

void mx_get_command_info(t_shell *m_s, char *command, int *flag, which_t which_options) {

    t_list *output= NULL;
    char *path = getenv("PATH");
    char **arr = NULL;

    if (!path)
        path = "";
	arr = mx_strsplit(path, ':');
	*flag = 0;
	check_builtin(m_s->builtin_list, command, &output, flag);
    check_path(arr, command, &output, flag);
    mx_del_strarr(&arr);

    print_path(output, *flag, command, which_options);
    mx_clear_list(&output);
}
