#include "ush.h"

static void mx_printerr_char(const char c) {
    write(2, &c, 1);
}

static void print_all(char *command, char *error, char arg) {
    mx_printerr("ush: ");
    mx_printerr(command);
    mx_printerr(": -");
    mx_printerr_char(arg);
    mx_printerr(": invalid option\n");
    mx_printerr(command);
    mx_printerr(": usage: ");
    mx_printerr(command);
    mx_printerr(error);
    mx_printerr(" \n");
}

int mx_count_options(char **args, char *options, char *command, char *error) {
    int n_options = 0;

    for (int i = 1; args[i] != NULL; i++) {
        if (args[i][0] != '-' || strcmp(args[i], "-") == 0) break;
        if (strcmp(args[i], "--") == 0) {
            n_options++;
            break;
        }
        for (int j = 1; j < mx_strlen(args[i]); j++) {
            if(mx_get_char_index(options,args[i][j]) < 0) {
                print_all(command, error, args[i][j]);
                return -1;
            }
        }
        n_options++;
    }
    return n_options;
}
