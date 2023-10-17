#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* for convert_number() */

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2

/* 1 if using system getline() */

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @string: a string
 * @next: points to the next node
 */



typedef struct liststr
{
	int num;
	char *string;
	struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} stat_t;

#define STAT_INIT \
	{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(stat_t *);
} builtin_table;

/* toem_fork.c */

int dsh(stat_t *, char **);
int cmd_builtin(stat_t *);
void get_cmd(stat_t *);
void _fork(stat_t *);

/* toem_paths.c */

int det_exec(stat_t *, char *);
char *duplicate_chars(char *, int, int);
char *f_cmd_path(stat_t *, char *, char *);

/* loophsh.c */

int loophsh(char **);

/* inputs.c */

void print_input(char *);
int write_char(char);
int write_fd(char c, int );
int print_fd(char *, int );

/* string.c */

int str_len(char *);
int string_cmp(char *, char *);
char *check_string(const char *, const char *);
char *string_concat(char *, char *);

/* putchar.c */

char *string_cpy(char *, char *);
char *string_dup(const char *);
void string_input(char *);
int put_char(char);

/* exits.c */

char *my_strcpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* token.c */

char **string_tok(char *, char *);
char **string_split(char *, char);

/* malloc.c */

char *fill_memory(char *, char, unsigned int);
void free_string(char **);
void *memory_realloc(void *, unsigned int, unsigned int);

/* pointer.c */

int free_pointer(void **);

/* alpha.c */

int interest(stat_t *);
int for_checks(char, char *);
int _alpha(int);
int _convert(char *);

/* numbers.c */

int conv_string(char *);
void handle_error(stat_t *, char *);
int pt_decimal(int, int);
char *conv_function(long int, int, int);
void replace_hash(char *);

/* inbuilt.c */

int _checkout(stat_t *);
int _change(stat_t *);
int _mylove(stat_t *);

/* alias.c */

int ma_history(stat_t *);
int mic_alias(stat_t *);

/* buffer.c */

ssize_t getline_minus(stat_t *);
int next_line(stat_t *, char **, size_t *);
void call_signal(int);

/* infor.c */

void init_info(stat_t *);
void grab_info(stat_t *, char **);
void info_freed(stat_t *, int);

/* my-env.c */

char *environ_var(stat_t *, const char *);
int print_env(stat_t *);
int init_env(stat_t *);
int remove_env(stat_t *);
int pop_env(stat_t *);

/* get-env.c */

char **my_environ(stat_t *);
int my_unsetenv(stat_t *, char *);
int my_setenv(stat_t *, char *, char *);

/* my-hist.c */

char *file_hist(stat_t *stat);
int create_hist(stat_t *stat);
int _readHist(stat_t *stat);
int _buildHist(stat_t *info, char *buf, int linecount);
int history_renum(stat_t *);

/* nodes.c */

list_t *nodeAdd(list_t **, const char *, int);
list_t *_endNode(list_t **, const char *, int);
size_t get_node_str(const list_t *);
int delete_indexNode(list_t **, unsigned int);
void _freeList(list_t **);

/* getlist.c */

size_t getLenght(const list_t *);
char **getStrings(list_t *);
size_t getList(const list_t *);
list_t *print_node(list_t *, char *, char);
ssize_t getNode(list_t *, list_t *);

/* replaces.c */

int chain_delim(stat_t *, char *, size_t *);
void chain_status(stat_t *, char *, size_t *, size_t, size_t);
int alias_replacement(stat_t *);
int var_replacement(stat_t *);
int str_replacement(char **, char *);

#endif
