#ifndef USH_H
#define USH_H

#include <sys/types.h>
#include <pwd.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/param.h>
#include <termios.h>
#include <signal.h>
#include <term.h>
#include <curses.h>
#include <malloc/malloc.h>
#include <limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>

#include "libmx.h"

// Exit
#define MX_EXIT_FAILURE 1
#define MX_EXIT_SUCCESS 0

// Jobs
#define MX_JOBS_NUMBER 10000
#define MX_STATUS_RUNNING 0
#define MX_STATUS_DONE 1
#define MX_STATUS_SUSPENDED 2
#define MX_STATUS_CONTINUED 3
#define MX_STAT_TERMINATED 4
#define MX_FILTER_ALL 0
#define MX_FILTER_DONE 1
#define MX_FILT_IN_PROGR 2
#define MX_FOREGROUND 1
#define MX_BACKGROUND 0
#define MAX_LEN 10

// Timers
#define MX_WNOHANG          0x00000001
#define MX_WUNTRACED        0x00000002
#define MX_W_INT(w)         (*(int *)&(w))  // Convert union wait to int
#define MX_WSTAT(x)         (MX_W_INT(x) & 0177)
#define MX_WSTOPPED         0177  // _WSTATUS if process is stopped
#define MX_WSTOPSIG(x)      (MX_W_INT(x) >> 8)
#define MX_WIFCONT(x)       (MX_WSTAT(x) == MX_WSTOPPED && MX_WSTOPSIG(x) == 0x13)
#define MX_WIFSTOPP(x)      (MX_WSTAT(x) == MX_WSTOPPED && MX_WSTOPSIG(x) != 0x13)
#define MX_WIFEXITED(x)     (MX_WSTAT(x) == 0)
#define MX_WIFSIGNALED(x)   (MX_WSTAT(x) != MX_WSTOPPED && MX_WSTAT(x) != 0)
#define MX_WTERMSIG(x)      (MX_WSTAT(x))
#define MX_W_EXITCODE(ret, sig)    ((ret) << 8 | (sig))
#define MX_W_STOPCODE(sig)  ((sig) << 8 | MX_WSTOPPED)
#define MX_WEXITED          0x00000004  // [XSI] Processes which have exitted
#define MX_WCONTINUED       0x00000010  // [XSI] Any child stopped then continu
#define MX_WNOWAIT          0x00000020  // [XSI] Leave process returned waitabl
#define MX_SIG_DFL          (void (*)(int))0
#define MX_SIG_IGN          (void (*)(int))1
#define MX_SIG_HOLD         (void (*)(int))5
#define MX_SIG_ERR          ((void (*)(int))-1)

// Colors
#define MX_BLK          "\x1B[30m"
#define MX_RED          "\x1B[31m"
#define MX_GRN          "\x1B[32m"
#define MX_YEL          "\x1B[33m"
#define MX_BLU          "\x1B[34m"
#define MX_MAG          "\x1B[35m"
#define MX_CYN          "\x1B[36m"
#define MX_WHT          "\x1B[37m"
#define MX_RESET        "\x1B[0m"
#define MX_RED_B        "\x1B[1;31m"
#define MX_RESET_B      "\x1B[1;31m"
#define MX_BLK_F_RED_B  "\x1B[0;30;41m"
#define MX_BLK_F_CYAN_B "\x1B[0;30;46m"
#define MX_BLOCK        "\x1B[0;34;46m"
#define MX_CHR          "\x1B[0;34;43m"
#define MX_DIR_T        "\x1B[0;30;42m"
#define MX_DIR_X        "\033[0;30;43m"
#define MX_BOLD_MAGENTA "\x1B[1;35m"
#define MX_BOLD_CYAN    "\x1B[1;36m"
#define MX_BOLD_RED     "\x1B[[1;31m"
#define MX_BOLD_BLUE    "\x1B[1;34m"

// Keyboard keys
#define MX_INPUT_SIZE  1024
#define MX_K_LEFT      4479771  // Edit keys
#define MX_K_RIGHT     4414235
#define MX_K_HOME      4741915
#define MX_K_END       4610843
#define MX_K_UP        4283163  // History keys
#define MX_K_DOWN      4348699
#define MX_P_UP        2117425947
#define MX_P_DOWN      2117491483
#define MX_C_PROMPT    42946
#define MX_CTRL_D      4
#define MX_CTRL_C      3
#define MX_CTRL_R      18
#define MX_BACKSCAPE   127
#define MX_TAB         9
#define MX_ENTER       10

// Abstract syntax
#define MX_PARSE_DELIM      ";|&><"
#define MX_QUOTE            "\"\'`$("
#define MX_DBLQ_EXCEPTIONS  "$`\"\\!"
#define MX_USH_TOK_DELIM    " \t\r\n\a"

// Macroces for recognizing delimeters.
#define MX_IS_SEP(x)            (!mx_strcmp(x, ";"))
#define MX_IS_FON(x)            (!mx_strcmp(x, "&"))
#define MX_IS_AND(x)            (!mx_strcmp(x, "&&"))
#define MX_IS_OR(x)             (!mx_strcmp(x, "||"))
#define MX_IS_PIPE(x)           (!mx_strcmp(x, "|"))
#define MX_IS_R_INPUT(x)        (!mx_strcmp(x, "<"))
#define MX_IS_R_INPUT_DBL(x)    (!mx_strcmp(x, "<<"))
#define MX_IS_R_OUTPUT(x)       (!mx_strcmp(x, ">"))
#define MX_IS_R_OUTPUT_DBL(x)   (!mx_strcmp(x, ">>"))
#define MX_IS_SEP_FIRST_LWL(x)  (x == SEP || x == FON || x == AND || x == OR)
#define MX_IS_REDIR_INP(x)      (x == R_INPUT || x == R_INPUT_DBL)
#define MX_IS_REDIR_OUTP(x)     (x == R_OUTPUT || x == R_OUTPUT_DBL)
#define MX_IS_REDIRECTION(x)    (MX_IS_REDIR_INP(x) || MX_IS_REDIR_OUTP(x))

// Operators
enum e_type {
    SEP,            // ;
    FON,            // &
    AND,            // &&
    OR,             // ||
    PIPE,           // |
    R_INPUT,        // <
    R_INPUT_DBL,    // <<
    R_OUTPUT,       // >
    R_OUTPUT_DBL,   // >>
    NUL
}   t_type;

// Abstract Syntax
typedef struct s_ast {
    char    **args;
    char    *token;
    int     type;
    struct  s_ast *next;
    struct  s_ast *left;
}              t_ast;

// Redirections
typedef struct s_redir {
    int     mypipe_redir[2];
    char    *input_path;   // < <<
    char    *output_path;  // > >>
    int     redir_delim;    // <, <<, >, >> from e_type
    struct  s_redir *next;
}              t_redir;

typedef struct s_jobs {
    int l;
    int r;
    int s;
}              t_jobs;

typedef struct cd_s {
    int s;
    int L;
    int P;
}              cd_t;

typedef struct pwd_s {
    int L;
    int P;
}              pwd_t;

typedef struct echo_s {
    int n;
    int e;
    int E;
}              echo_t;

typedef struct which_s {
    int s;
    int a;
}              which_t;

typedef struct env_s {
    int i;
    int u;
    int P;
}              env_t;

typedef struct  s_export {
    char *name;
    char *value;
    struct s_export *next;
}               t_export;

typedef struct  s_stack {
    int         size;       // Size = MX_JOBS_NUMBER
    int*        stack;
    int         top;        // Index of last add job
    int         last;       // Current job gor fg
    int         prev_last;
}              t_stack;

typedef struct s_env_builtin  {
    env_t       env_options;
    int         n_options;
    int         n_variables;
    int         n_args;
    t_export    *env_list;
    t_export    *env_params;
    char        *path;
}              t_env_builtin;

typedef struct s_process {
    char    *fullpath;     // For execve
    char    **argv;        // Gets in create_job.c
    char    *command;
    char    *arg_command;
    char    *input_path;   // < <<
    char    *output_path;  // > >>
    int     redir_delim;    // <, <<, >, >> from e_type
    t_redir *redirect;  // New
    int     c_input;        // Count_redir_input
    int     c_output;       // Count_redir_output
    int     *r_infile;
    int     *r_outfile;
    pid_t   pid;
    int     exit_code;
    char    *path;
    char    **env;
    int     status;         // Status RUNNING DONE SUSPENDED CONTINUED TERMINATED
    int     foregrd;
    int     pipe;           // Gets in create_job.c
    int     delim;          // Gets in create_job.c (first - | || &&) (end - ; &)
    int     type;  // COMMAND_BUILTIN = index in m_s->builtin_list; default = 0
    struct s_process *next;  // Next process in pipeline
    pid_t   pgid;
    int     infile;
    int     outfile;
    int     errfile;
}             t_process;

// Pipeline of processes
typedef struct s_job {
    int     job_id;             // Number in jobs control
    int     job_type;           // 0 if normal, or enum &&, || of previos job
    char    *command;          // Command line, used for messages
    t_process *first_pr;    // List of processes in this job
    pid_t   pgid;             // Process group ID
    char    *path;
    char    **env;
    int     flag;
    int     exit_code;
    int     foregrd;            // Foregrd = 1 or background execution = 0
    struct termios tmodes;  // Saved terminal modes
    int     infile;
    int     outfile;
    int     errfile;
    int     stdin;              // Standard i/o channels
    int     stdout;             // Standard i/o channels
    int     stderr;             // Standard i/o channels
    struct s_job *next;     // Next job separated by ";" "&&" "||"
}             t_job;

typedef struct s_shell {
    int     argc;
    char    **argv;            // Check usage, becouse the same in process
    char    **envp;            // Not used
    int     exit_code;          // Return if exit
    t_job   *jobs[MX_JOBS_NUMBER];  // Arr jobs
    t_stack *jobs_stack;
    int     max_number_job;     // Number of added jobs + 1
    char    **builtin_list;    // Buildin functions
    int     exit_flag;      // Defaults 0, cheack if you have suspended jobs
    char    **history;
    int     history_count;
    int     history_index;
    int     history_size;
    struct termios tmodes;
    struct termios t_original;
    struct termios t_custom;
    bool    custom_terminal;
    pid_t   shell_pgid;
    char    *pwd;
    char    *prompt;
    char    *git;
    int     line_len;
    int     prompt_status;
    t_export *exported;
    t_export *variables;
    t_export *functions;
    t_export *aliases;
    int     redir;
    char    *kernal;
}             t_shell;

// Abstract Syntax
t_ast **mx_ast_creation(char *line, t_shell *m_s);
t_ast *mx_ush_parsed_line(t_ast *res, char *line, t_shell *m_s, int old_t);
char *mx_get_token_and_delim(char *line, int *i, int *type);
char **mx_parce_tokens(char *line);
char *mx_strtok (char *s, const char *delim);

t_ast **mx_ast_parse(t_ast *parsed_line);
void mx_ast_push_back(t_ast **head, char *arg, int type);
void mx_ast_push_back_redirection(t_ast **head, char *arg, int type);
void mx_ast_clear_list(t_ast **list);
void mx_ast_clear_all(t_ast ***list);               // In mx_ast_clear_list.c

void mx_redir_push_back(t_redir **head, char *path, int type);
void mx_redir_clear_list(t_redir **list);

bool mx_check_parce_errors(char *line);
bool mx_parse_error(char *c, int k);
char *mx_syntax_error(char *c);
bool mx_unmached_error(char c);
t_ast *mx_parse_error_ush(int type, t_ast *res, char *line);

void mx_ast_print(t_ast **ast);                     // In mx_ast_creation.c
char *mx_ush_read_line(t_shell *m_s);

// Filters
char **mx_filters(char *arg, t_shell *m_s);

char *mx_subst_tilde(char *s, t_export *variables);
char *mx_add_login(char *home, char *prefix);
char *mx_substr_dollar(char *s, t_export *variables);
char *mx_subst_command(char *s, t_shell *m_s);

bool mx_get_functions(char *line, t_shell *m_s);
void mx_get_aliases(char *line, t_shell *m_s);

// Quote manager
int mx_get_char_index_quote(char *s, char *c, char *q);
void mx_strtrim_quote(char **str);

// Initialization
t_shell *mx_init_shell(int argc, char **argv);
void mx_set_shell_grp(t_shell *m_s);

// Terminal
void mx_termios_save(t_shell *m_s);
void mx_termios_restore(t_shell *m_s);

// Loop
void mx_ush_loop(t_shell *m_s);
t_job *mx_create_job(t_shell *m_s, t_ast *list);
void mx_push_process_back(t_process **process, t_shell *m_s, t_ast *list);
void mx_clear_process(t_process *p);
void mx_launch_job(t_shell *m_s, t_job *job);

int mx_set_redirections(t_shell *m_s, t_job *job, t_process *p);
void mx_count_redir(t_process *p);
void mx_set_r_infile(t_shell *m_s, t_job  *job, t_process *p);
void mx_set_r_outfile(t_shell *m_s, t_job *job, t_process *p);

int mx_red_in(t_job *job, t_process *p, char *input_path, int j);
int mx_red_in_d(t_job *job, t_process *p, char *input_path, int j);

void mx_dup_fd(t_process *p);
int mx_launch_process(t_shell *m_s, t_process *p, int job_id);
int mx_builtin_commands_idex(t_shell *m_s, char *command);
void mx_pgid(t_shell *m_s, int job_id, int child_pid);

// Builtin commands
int mx_env(t_shell *m_s, t_process *p);
int mx_echo(t_shell *m_s, t_process *p);
int mx_jobs(t_shell *m_s, t_process *p);
int mx_fg(t_shell *m_s, t_process *p);
int mx_bg(t_shell *m_s, t_process *p);
int mx_cd(t_shell *m_s, t_process *p);
int mx_pwd(t_shell *m_s, t_process *p);
int mx_export(t_shell *m_s, t_process *p);
int mx_unset(t_shell *m_s, t_process *p);
int mx_which(t_shell *m_s, t_process *p);
int mx_exit(t_shell *m_s, t_process *p);
int mx_set(t_shell *m_s, t_process *p);
int mx_chdir(t_shell *m_s, t_process *p);
int mx_kill(t_shell *m_s, t_process *p);
int mx_true(t_shell *m_s, t_process *p);
int mx_alias(t_shell *m_s, t_process *p);           // In mx_set.c
int mx_declare(t_shell *m_s, t_process *p);         // In mx_set.c
int mx_false(t_shell *m_s, t_process *p);

// Signals
void mx_sig_h(int signal);

// Jobs
int mx_get_next_job_id(t_shell *m_s);
int mx_insert_job(t_shell *m_s, t_job *job);
void mx_remove_job(t_shell *m_s, int job_id);
void mx_remove_job_from_panel(t_shell *m_s, int job_id);
int mx_get_proc_count(t_shell *m_s, int job_id, int filter);
void mx_set_process_status(t_shell *m_s, int pid, int status);
int mx_set_job_status(t_shell *m_s, int job_id, int status);
int mx_get_job_status(t_shell *m_s, int job_id, int status);
void mx_set_last_job(t_shell *m_s);
int mx_g_find_job(t_shell *m_s, char *arg);
void mx_dup_close(int inp, int out);

int mx_job_is_running(t_shell *m_s, int job_id);

void mx_init_jobs_stack(t_shell *m_s);
void mx_push_to_stack (t_shell *m_s, int job);
void mx_pop_from_stack(t_shell * m_s, int job);
bool mx_get_from_stack(t_shell *m_s, int job_id);
void mx_print_stack (t_shell *m_s);

int mx_job_id_by_pid(t_shell *m_s, int pid);
int mx_get_pgid_by_job_id(t_shell *m_s, int job_id);
int mx_job_completed(t_shell *m_s, int job_id);

void mx_print_pid_process_in_job(t_shell *m_s, int id);  // If foreg execution
void mx_print_job_status(t_shell *m_s, int job_id, int flag);
void mx_print_args_in_line(char **res, const char *delim);

void mx_check_jobs(t_shell *m_s);              // Waitpid any process
int mx_wait_job(t_shell *m_s, int id);         // Waitpid process in job group
void mx_destroy_jobs(t_shell *m_s, int id);    // Free job memory

void mx_err_j(char *arg0, char *arg1, char *arg2, char *arg3);
int mx_check_args(t_shell *m_s, t_process *p);  // Use in fg and bg

void mx_printstr(const char *s);
void mx_printerr(const char *s);
char *mx_normalization (char *point, char *pwd);
void mx_push_export(t_export **list, void *name, void *value);
t_export *mx_set_variables(void);
t_export *mx_set_export(void);
int mx_count_options(char **args, char *options, char *command, char *error);
void mx_set_variable(t_export *export, char *name, char *value);
char mx_get_type(struct stat file_stat);
int mx_launch_bin(t_process *p, char *path, char **env);
int mx_set_parametr(char **args,  t_shell *m_s);


int mx_launch_builtin(t_shell *m_s, t_process *p, int job_id);
char *mx_get_git_info(void);
void mx_clear_all(t_shell *m_s);
char *mx_go_somewere(t_process *p, int n_options);
char *mx_go_back(void);
char *mx_go_home(void);
void mx_change_dir(char *point, cd_t cd_options, t_shell *m_s, int *exit_code);
char *mx_strdup_from(char *str, int index);
void mx_export_or_error(char *arg, t_export *export, t_export *variables, int *exit_code);
void mx_clear_export(t_export *list);
void mx_set_data(t_env_builtin *env, char *args[]);
void mx_launch_command( t_process *p, t_env_builtin *env, int *exit_code);
int mx_count_env_options(char **args, t_env_builtin *env);
void mx_escape_seq(t_process *p, int i, echo_t echo_options);
void mx_get_command_info(t_shell *m_s, char *command, int *flag, which_t which_options);
char *mx_get_keys(t_shell *m_s);
void mx_print_prompt(t_shell *m_s);
void mx_edit_prompt(t_shell *m_s);
void mx_edit_command(int keycode, int *position, char **line, t_shell *m_s);
void mx_exec_signal(int keycode, char **line, int *position, t_shell *m_s);
char *mx_get_line(t_shell *m_s);
int mx_get_flag(char **args);
void mx_sheck_exit(t_shell *m_s, t_process *p);
int mx_add_option(char **args, int *i, int *n_options, t_env_builtin *env);
void mx_env_err(int *flag, int *exit_code, char option);
void mx_print_env_error(char option, char *error);
void mx_clear_data(char *name, char *value);
void mx_print_error(char *command, char *error);
char *mx_get_shlvl(void);
void mx_export_value(t_export *export, char *name, char *value);

void mx_dup2_fd(int *fd1, int *fd2);
char *mx_run_subshell(char *substr, t_shell *m_s);
char *mx_subs_output(char **res);

void mx_print_fd(t_process  *p);

#endif
