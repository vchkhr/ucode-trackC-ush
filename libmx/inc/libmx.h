#ifndef LIBMX_H
#define LIBMX_H

#include <malloc/malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wchar.h>

// Utilities
void mx_printchar(char);
void mx_print_unicode(wchar_t);
void mx_printstr(const char *);
void mx_print_strarr(char **, const char *);
void mx_printint(int);
double mx_pow(double, unsigned int);
int mx_sqrt(int);
char *mx_nbr_to_hex(unsigned long);
unsigned long mx_hex_to_nbr(const char *);
char *mx_itoa(int);
void mx_foreach(int *, int, void (*)(int));
int mx_binary_search(char **, int, const char *, int *);
int mx_bubble_sort(char **, int);
int mx_quicksort(char **, int, int);

// Strings
int mx_strlen(const char *);
void mx_swap_char(char *, char *);
void mx_str_reverse(char *);
void mx_strdel(char **);
void mx_del_strarr(char ***);
int mx_get_char_index(const char *str, char c);
char *mx_strdup(const char *);
char *mx_strndup(const char *, size_t);
char *mx_strcpy(char *, const char *);
char *mx_strncpy(char *, const char *, int);
int mx_strcmp(const char *, const char *);
char *mx_strcat(char *restrict, const char *restrict);
char *mx_strstr(const char *, const char *);
int mx_get_substr_index(const char *, const char *);
int mx_count_substr(const char *, const char *);
int mx_count_words(const char *, char);
char *mx_strnew(int);
char *mx_strtrim(const char *);
char *mx_del_extra_spaces(const char *);
char **mx_strsplit(const char *, char);
char *mx_strjoin(const char *, const char *);
char *mx_file_to_str(const char *);
char *mx_replace_substr(const char *, const char *, const char *);
int mx_read_line(char **lineptr, size_t buf_size, char delim, const int fd);

// Memory
void *mx_memset(void *, int, size_t);
void *mx_memcpy(void *restrict, const void *restrict, size_t);
void *mx_memccpy(void *restrict, const void *restrict, int c, size_t);
int mx_memcmp(const void *, const void *, size_t);
void *mx_memchr(const void *, int, size_t);
void *mx_memrchr(const void *, int, size_t);
void *mx_memmem(const void *, size_t, const void *, size_t);
void *mx_memmove(void *, const void *, size_t);
void *mx_realloc(void *, size_t);

// Lists
typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;

t_list *mx_create_node(void *);
void mx_push_front(t_list **, void *);
void mx_push_back(t_list **, void *);
void mx_pop_front(t_list **);
void mx_pop_back(t_list **);
int mx_list_size(t_list *);
t_list *mx_sort_list(t_list *, bool (*)(void *, void *));

// Features
int mx_atoi(const char *);
bool mx_isspace(const char);
bool mx_isdigit(const char);
bool mx_isalpha(const char);
char *mx_strchr(const char *, int);
int mx_strncmp(const char *, const char *, int);
int mx_strnlen(const char *, char);
int mx_filelen(const char *);
void mx_printlist(t_list *);
void mx_printerr(const char *);
void mx_printerr_red(char *c);
int mx_strlen_arr(char **s);

#endif
