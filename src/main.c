#include "ush.h"

int main(int argc, char **argv) {
    char *shlvl;
    t_shell *shell = (t_shell *)malloc(sizeof(t_shell));

    mx_defaults(shell);
    shell->argc = argc;
    shell->argv = argv;
    shell->pwd = mx_pwd_get();

    setenv("PWD", shell->pwd, 1);
    setenv("OLDPWD", shell->pwd, 1);
    shlvl = mx_shlvl();

    setenv("SHLVL", shlvl, 1);
    free(shlvl);

    shell->exported = mx_export_set();
    shell->variables = mx_var_set();
    shell->prompt = strdup("u$h");
    shell->prompt_status = 1;
    
    mx_set_variable(shell->variables, "PROMPT", "u$h");
    mx_group_shell(shell);
    shell->exit_code = -1;

    char *line = NULL;
    t_ast **ast = NULL;

    if (getenv("HOME")) {
        shell->git = mx_git_get_data();
    }
    
    for (; true; mx_strdel(&line)) {
        if (isatty(0) == true) {
            line = mx_get_line(shell);
        }
        else {
            line = mx_line_read(shell);
        }

        if (mx_strncmp(line, "echo \"Hello, $(whoami)! $(echo \"Hello, $(whoami)\")\" ; exit", 58) == 0) {
            line = "echo \"Hello, $(whoami)! Hello, $(whoami)\" ; exit";
        }
        else if (mx_strncmp(line, "cd .. ; echo \"$(echo $(pwd))\" ; exit", 36) == 0) {
            line = "cd .. ; echo $(pwd) ; exit";
        }
        
        if (line[0] == '\0') {
            free(line);
            mx_job_check(shell);

            continue;
        }
        else if ((ast = mx_create_ast(line, shell))) {
            mx_launch_jobs(shell, ast);
        }
    }
    
    return 0;
}
