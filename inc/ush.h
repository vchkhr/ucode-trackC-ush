#ifndef USH_H
#define USH_H

#include "libmx.h"

#include <pwd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <signal.h>
#include <termios.h>

#define MAX_LEN 10
#define MX_WSTAT(x) ((*(int *)&(x)) & 0177)
#define MX_WSTOPSIG(x) ((*(int *)&(x)) >> 8)
#define MX_SIG_DFL (void (*)(int))0
#define MX_SIG_IGN (void (*)(int))1

typedef struct s_ast {
    char **arguments;
    char *token;
    int type;
    struct s_ast *next;
    struct s_ast *previous;
}              t_ast;

typedef struct c_cd {
    int l;
    int p;
    int s;
}              t_cd;

typedef struct s_echo {
    int E;
    int e;
    int n;
}              t_echo;

typedef struct s_enivronment {
    int P;
    int i;
    int u;
}              t_environment;

typedef struct  s_export {
    char *name;
    char *value;
    struct s_export *next;
}               t_export;

typedef struct s_jobs {
    int left;
    int right;
    int stop;
}              t_jobs;

typedef struct s_pwd {
    int l;
    int p;
}              t_pwd;

typedef struct s_redir {
    char *input;
    char *output;
    int delimiter;
    int redirect[2];
    struct  s_redir *next;
}              t_redir;

typedef struct  s_stack {
    int first;
    int last;
    int previous;
    int size; 
    int *stack;
}              t_stack;

typedef struct s_which {
    int a;
    int s;
}              t_which;

typedef struct s_default  {
    char *path;
    int arguments;
    int options;
    int variables;
    t_environment environment_options;
    t_export *list;
    t_export *parameters;
}              t_default;

typedef struct s_process {
    char **arguments_amount;
    char **env;
    char *argument_command;
    char *command;
    char *full_path;
    char *input_path;
    char *output_path;
    char *path;
    int *r_infile;
    int *r_outfile;
    int c_input;
    int c_output;
    int delim;
    int errfile;
    int exit_code;
    int foregrd;
    int infile;
    int outfile;
    int pipe;
    int redir_delim;
    int status;
    int type;
    pid_t pgid;
    pid_t pid;
    struct s_process *next;
    t_redir *redirect;
}             t_process;

typedef struct s_job {
    char **env;
    char *command;
    char *path;
    int errfile;
    int exit_code;
    int flag;
    int foregrd;
    int infile;
    int job_id;
    int job_type;
    int outfile;
    int stderr;
    int stdin;
    int stdout;
    pid_t pgid;
    struct s_job *next;
    struct termios tmodes;
    t_process *first_pr;
}             t_job;

typedef struct s_shell {
    bool custom_terminal;
    char **argv;
    char **default_list;
    char **envp;
    char **history;
    char *git;
    char *kernal;
    char *prompt;
    char *pwd;
    int argc;
    int exit_code;
    int history_count;
    int history_index;
    int history_size;
    int line_len;
    int max_number_job;
    int prompt_status;
    int redir;
    int result;
    pid_t shell_pgid;
    struct termios t_custom;
    struct termios t_original;
    struct termios tmodes;
    t_export *aliases;
    t_export *exported;
    t_export *functions;
    t_export *variables;
    t_job *jobs[10000];
    t_stack *jobs_stack;
}             t_shell;

bool mx_check_allocation_error(const void *);
bool mx_check_errors_parsing(char *);
bool mx_check_parsing(char *, int);
bool mx_check_parsing_loop(char *);
bool mx_check_substitution_result(char **, char **, int *);
bool mx_check_token(char *, char *);
bool mx_error_parse(char *, int);
bool mx_get_functions(char *, t_shell *);
bool mx_isdelim (char c, char *);
bool mx_quotes_check(char *);
bool mx_unmatched_error(char);
char **mx_filters(char *, t_shell *);
char **mx_get_alias_tokens(char *, t_shell *);
char **mx_get_array(char *);
char **mx_get_environment(t_export *);
char **mx_get_launch_arguments(t_process *, int);
char **mx_strdup_arr(char **);
char **mx_substitutions(char **, t_shell *);
char **mx_tokens_create(char **, int *);
char **mx_tokens_parse(char *);
char *mx_chpwd(char **, int , t_shell *);
char *mx_chpwd_cd(char **, int , t_shell *);
char *mx_combine_strings(char *, int , t_shell *);
char *mx_delimiter_error_print(int);
char *mx_directory(char *, char *);
char *mx_directory_fill(char **);
char *mx_error_bin(char **, char *, int *);
char *mx_error_process(char **, char *, int *);
char *mx_error_syntax(char *);
char *mx_error_usage();
char *mx_get_keys(t_shell *);
char *mx_get_line(t_shell *);
char *mx_get_option(char);
char *mx_get_parameter(char **, int *, int , int *);
char *mx_get_quotes(char *, const char *, char *);
char *mx_get_token(char *, int *, int *);
char *mx_get_value(char *, int);
char *mx_get_var(char *, int);
char *mx_git_get_data();
char *mx_hex_calculate(unsigned long , int);
char *mx_home();
char *mx_line_read(t_shell *);
char *mx_nbr_to_hex(unsigned long);
char *mx_next(t_process *, int);
char *mx_normalize(char *, char *);
char *mx_output_substring(char **);
char *mx_parent_shell(t_shell *, int *, int *, int);
char *mx_path_check_bin(char **, char *);
char *mx_path_check_process(char **, char *);
char *mx_prefix(char *, int *);
char *mx_previous();
char *mx_pwd_get();
char *mx_result_get(char *, char *, char *);
char *mx_shell_execute(t_shell *, int *, int *);
char *mx_shell_run(char *, t_shell *);
char *mx_shlvl();
char *mx_slash_replace(char *, t_echo *);
char *mx_str_delimiter(char *, const char *);
char *mx_strdup_data(char *, int);
char *mx_strdup_index(char *, int);
char *mx_strdup_parameter(char *, int);
char *mx_string_delimiter(char *, const char *, char **);
char *mx_string_dollar(char *, t_export *);
char *mx_string_substitution(char *, t_export *, int);
char *mx_strjoin_free(char *, char const *);
char *mx_substitude_commands(char *, t_shell *);
char *mx_substitude_quotes(char *, t_export *, int *, int *);
char *mx_substitude_tilde(char *, t_export *);
char *mx_substitution_tilde(char *, t_export *);
char *mx_substr_replace_cd(char *, char *, char *);
char *mx_substr_replace_chdir(char *, char *, char *);
char *mx_substr_replace_echo(char *, char *, char *);
char *mx_substritution(char *, int *);
char *mx_tilde_result(char *, t_export *);
char *mx_user(char *, char *);
char *mx_user_replace(char *);
char *mx_value_substitution(char *, t_export *);
char *mx_var(t_shell *, char *);
char *mx_variable_substitution(char *, int *);
char mx_check_quote(char *, int *);
char mx_get_file_stat(struct stat);
int mx_add_parameter(char *, t_export **, char);
int mx_alias(t_shell *, t_process *);
int mx_arguments_count_chdir(char **, int);
int mx_arguments_count_export(char **, int);
int mx_arguments_count_jobs(char **, int);
int mx_arguments_count_kill(char **);
int mx_arguments_count_pwd(char **, int);
int mx_arguments_count_unset(char **, int);
int mx_bin_start(t_process *, char *, char **);
int mx_builting_start(t_shell *, t_process *, int);
int mx_check_arguments(t_shell *, t_process *);
int mx_check_id_export(char *);
int mx_command_cd(t_shell *, t_process *);
int mx_command_index(t_shell *, char *);
int mx_count_arguments(char **, int);
int mx_count_environment_options(char **, t_default *);
int mx_declare(t_shell *, t_process *);
int mx_directory_change(t_shell *, t_process *);
int mx_echo(t_shell *, t_process *);
int mx_environment(t_shell *, t_process *);
int mx_exit(t_shell *, t_process *);
int mx_export(t_shell *, t_process *);
int mx_fg(t_shell *, t_process *);
int mx_find(t_shell *, t_process *);
int mx_first_level(t_ast *);
int mx_flag_get(char **);
int mx_flag_redirect(int);
int mx_get_arguments_amout(char **, int);
int mx_get_bg_job_id(t_shell *, t_process *);
int mx_get_char_index_reverse(const char *, char);
int mx_get_delimiter(char *, int *);
int mx_get_job_status(t_shell *, int , int);
int mx_get_next_job_id(t_shell *);
int mx_get_pgid(t_shell *, int);
int mx_get_process(t_shell *, int , int);
int mx_get_token_type(char *);
int mx_id_check(char *);
int mx_index_char_quote(char *, char *, char *);
int mx_insert_job(t_shell *, t_job *);
int mx_job_completed(t_shell *, int);
int mx_job_execute_start(t_shell *, t_job *, int);
int mx_job_find(t_shell *, char *);
int mx_job_id_by_pid(t_shell *, int);
int mx_job_id_get(t_shell *, t_process *);
int mx_job_is_running(t_shell *, int);
int mx_job_status(t_shell *, int , int);
int mx_job_type(t_ast **, int);
int mx_job_wait(t_shell *, int);
int mx_jobs(t_shell *, t_process *);
int mx_jobs(t_shell *, t_process *);
int mx_kill(t_shell *, t_process *);
int mx_option_add(char **, int *, int *, t_default *);
int mx_options_count(char **, char *, char *, char *);
int mx_options_count_echo(char **);
int mx_options_count_set(char **);
int mx_path_check_cd(char *, t_cd);
int mx_pid(t_shell *, t_process *);
int mx_pid_check(char *);
int mx_proccess_launch(t_shell *, t_process *, int);
int mx_pwd(t_shell *, t_process *);
int mx_redirect_d(t_job *, t_process *, char *, int);
int mx_redirect_in(t_job *, t_process *, char *, int);
int mx_redirections(t_shell *, t_job *, t_process *);
int mx_set(t_shell *, t_process *);
int mx_set_0(t_shell *, t_process *);
int mx_set_1(t_shell *, t_process *);
int mx_set_parameter(char **, t_shell *);
int mx_signal_send(t_shell *, t_process *, int , int);
int mx_strlen_arr(char **);
int mx_unset(t_shell *, t_process *);
int mx_vars_count(char **, int);
struct termios mx_term_disable();
t_ast **mx_create_ast(char *, t_shell *);
t_ast **mx_parse_ast(t_ast *);
t_ast *mx_all_commands(t_ast *, char *, t_shell *, int);
t_ast *mx_error_ush(int , t_ast *, char *);
t_ast *mx_node_create(char *, int);
t_ast *mx_redirect_push(t_ast **, t_ast **);
t_default *mx_initialise_environment(t_process *);
t_export *mx_create_node_export(void *, void *);
t_export *mx_export_set();
t_export *mx_var_set();
t_job *mx_job_create(t_shell *, t_ast *);
t_job *mx_job_init(t_process *);
t_process *mx_process_create(t_shell *, t_ast *);
t_process *mx_process_initialize(t_ast *);
t_redir *mx_redirect_create_node(char *, int);
unsigned long mx_hex_to_nbr(const char *);
void mx_append(t_ast **, char *, int);
void mx_append_redirect(t_ast **, char *, int);
void mx_backspace_reverse(int *, char *);
void mx_change_directory(char *, t_cd , t_shell *, int *);
void mx_char_add(int *, char *, int , t_shell *);
void mx_char_quote(char *, int *, char *);
void mx_check_default(char **, char *, t_list **, int *);
void mx_check_exit(t_shell *, t_process *);
void mx_check_export(char *, t_export *, t_export *, int *);
void mx_child_process(t_shell *, t_process *, int , int);
void mx_clear(t_shell *);
void mx_clear_list(t_list **);
void mx_clear_list_x2(t_ast **);
void mx_clear_list_x3(t_ast ***);
void mx_close_dup(int , int);
void mx_command_exit(int , int *, char **, t_shell *);
void mx_command_launch( t_process *, t_default *, int *);
void mx_customize(t_shell *);
void mx_data_clear(char *, char *);
void mx_data_get_aliases(char *, char **, char **);
void mx_data_get_export(char *, char **, char **, t_export *);
void mx_data_get_set_parameter(char *, char **, char **);
void mx_data_set(t_default *, char *[]);
void mx_default_exec(t_shell *, int (*builtin_functions[]) (t_shell *m_s, t_process *p), t_process *);
void mx_default_fork(t_shell *, int , int (*builtin_functions[]) (t_shell *m_s, t_process *p), t_process *);
void mx_defaults(t_shell *);
void mx_delete(char **, int);
void mx_directory_process(char *, char *, int *, char **);
void mx_dup2(int *, int *);
void mx_edit_arguments(int , t_process *);
void mx_environment_error(int *, int *, char);
void mx_environment_print(t_export *);
void mx_error_arguments(char *, char *, char *, char *);
void mx_error_print(char *, char *);
void mx_error_print_bin(char *, char *);
void mx_error_print_cd(char *);
void mx_error_print_char(const char);
void mx_error_print_environment(char , char *);
void mx_error_print_export(char *, int *);
void mx_error_unset(t_shell *, char *, int *);
void mx_export_clear(t_export *);
void mx_export_parameter(t_export *, char *, char *);
void mx_export_print(t_export *);
void mx_export_push(t_export **, void *, void *);
void mx_fill_options(int , t_which *, char **);
void mx_get_aliases(char *, t_shell *);
void mx_get_code_exit(t_process *, int *, int *, int *);
void mx_get_params(t_export *, t_export *, t_default *);
void mx_get_set_data(int , char **, t_default *);
void mx_git_find(int *, char **, char **);
void mx_git_get(struct dirent *ds, char **, int *, char *);
void mx_group_shell(t_shell *);
void mx_help_start(t_shell *, t_job *, int , int);
void mx_info_command(t_shell *, char *, int *, t_which);
void mx_info_command(t_shell *, char *, int *, t_which);
void mx_input_read(int *, int *, char *);
void mx_job_check(t_shell *);
void mx_job_destroy(t_shell *, int);
void mx_job_dup(t_process *);
void mx_job_execute(t_job *);
void mx_job_help(t_shell *, t_job *, t_process *, int);
void mx_job_kill(t_shell *, t_process *, int);
void mx_job_last(t_shell *);
void mx_job_print(t_process *);
void mx_job_stack(t_shell *);
void mx_jobs_info(t_shell *, t_process *, t_jobs , int);
void mx_jobs_info(t_shell *, t_process *, t_jobs , int);
void mx_jod_status_print(t_shell *, int , int);
void mx_key_backscape(int *, char *);
void mx_key_down(t_shell *, char **, int *);
void mx_key_select(int *, char **, int , t_shell *);
void mx_key_up(t_shell *, char **, int *);
void mx_last_type(t_ast **, int);
void mx_launch_job(t_shell *, t_job *);
void mx_launch_jobs(t_shell *, t_ast **);
void mx_left_print(t_ast *);
void mx_mx_environment(char *, t_shell *, t_cd , int *);
void mx_name_delete(t_export **, char *);
void mx_names_delete(t_export **, char *);
void mx_options_fill(int , t_cd *, char **);
void mx_options_fill_cd(int , t_cd *, char **);
void mx_options_fill_echo(char **, t_echo *, int);
void mx_options_fill_jobs(int , t_jobs *, char **);
void mx_options_fill_pwd(int , t_pwd *, char **);
void mx_path_check_command_info(char **, char *, t_list **, int *);
void mx_path_set(t_shell *);
void mx_pgid(t_shell *, int , int);
void mx_pid_kill(t_shell *, t_process *, int);
void mx_pipe(t_shell *, t_job *, int [], int);
void mx_print(char *, char *, char);
void mx_print_arguments(char **, const char *);
void mx_print_color(char *, char *);
void mx_print_command(t_shell *, char *, int , int);
void mx_print_mask(t_shell *, t_jobs , int);
void mx_print_mask(t_shell *, t_jobs , int);
void mx_print_path(t_list *, int , char *, t_which);
void mx_print_pid(t_shell *, int);
void mx_print_spaces(int);
void mx_print_strarr_in_line(char **, const char *);
void mx_printerr(const char *);
void mx_printstr(const char *);
void mx_process_append(t_process **, t_shell *, t_ast *);
void mx_process_bin(t_process *, char *, char **, int *);
void mx_process_clear(t_process *);
void mx_process_status(t_shell *, int , int);
void mx_prompt_edit(t_shell *);
void mx_prompt_print(t_shell *);
void mx_push_func(t_ast **, char *, int , t_shell *);
void mx_pwd_print(char *, int *, t_shell *, t_pwd);
void mx_redirect_append(t_redir **, char *, int);
void mx_redirect_clear(t_redir **);
void mx_redirects_count(t_process *);
void mx_redirects_in(t_shell *, t_job *, t_process *);
void mx_redirects_out(t_shell *, t_job *, t_process *);
void mx_remove_job(t_shell *, int);
void mx_remove_job_from_panel(t_shell *, int);
void mx_replace_e(int *, char *);
void mx_sequence_escape(t_process *, int , t_echo);
void mx_set_buff_zero(void *, size_t);
void mx_set_variable(t_export *, char *, char *);
void mx_signal_execution(int , char **, int *, t_shell *);
void mx_stack_pop(t_shell *, int);
void mx_stack_push(t_shell *, int);
void mx_term_enable(struct termios safe);
void mx_trim_quote(char **);
void mx_trim_quote_help(char *, char *, int *, int *);
void mx_ush_exit(t_shell *);
void mx_value_export(t_export *, char *, char *);

#endif
