#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>



/* in order to read/write buffers */

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* this is for command chaining */

#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* in order to convert_number() */

#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED        2


#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096

extern char **environ;



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
} info_t;

#define INFO_INIT \
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
	int (*func)(info_t *);
} builtin_table;

/* for fork.c */

int dsh(info_t *, char **);
int cmd_builtin(info_t *);
void get_cmd(info_t *);
void _fork(info_t *);

/* for paths.c */

int det_exec(info_t *, char *);
char *duplicate_chars(char *, int, int);
char *f_cmd_path(info_t *, char *, char *);

/* loophsh.c */

int loophsh(char **);

/* for inputs.c */

void print_input(char *);
int write_char(char);
int write_fd(char c, int );
int print_fd(char *, int );

/* for spring.c */

int str_len(char *);
int string_cmp(char *, char *);
char *check_string(const char *, const char *);
char *string_concat(char *, char *);

/* for putchar.c */

char *string_cpy(char *, char *);
char *string_dup(const char *);
void string_input(char *);
int put_char(char);

/* for strncat.c */

char *my_strcpy(char *, char *, int);
char *my_strncat(char *, char *, int);
char *my_strchr(char *, char);

/* for token.c */

char **string_tok(char *, char *);
char **string_split(char *, char);

/* for malloc.c */

char *fill_memory(char *, char, unsigned int);
void free_string(char **);
void *memory_realloc(void *, unsigned int, unsigned int);

/* for pointer.c */

int free_pointer(void **);

/* for alpha.c */

int interest(info_t *);
int for_checks(char, char *);
int _alpha(int);
int _convert(char *);

/* for numbers.c */

int conv_string(char *);
void handle_error(info_t *, char *);
int pt_decimal(int, int);
char *conv_function(long int, int, int);
void replace_hash(char *);

/* for inbuilt.c */

int _checkout(info_t *);
int _change(info_t *);
int _mylove(info_t *);

/* for alias.c */

int ma_history(info_t *);
int mic_alias(info_t *);

/* for buffer.c */

ssize_t getline_minus(info_t *);
int next_line(info_t *, char **, size_t *);
void call_signal(int);

/* for infor.c */

void init_info(info_t *);
void grab_info(info_t *, char **);
void info_freed(info_t *, int);

/* for my-env.c */

char *environ_var(info_t *, const char *);
int print_env(info_t *);
int init_env(info_t *);
int remove_env(info_t *);
int pop_env(info_t *);

/* for get-env.c */

char **my_environ(info_t *);
int my_unsetenv(info_t *, char *);
int my_setenv(info_t *, char *, char *);

/* for my-hist.c */

char *file_hist(info_t *stat);
int create_hist(info_t *stat);
int _readHist(info_t *stat);
int _buildHist(info_t *info, char *buf, int linecount);
int history_renum(info_t *);

/* for nodes.c */

list_t *nodeAdd(list_t **, const char *, int);
list_t *_endNode(list_t **, const char *, int);
size_t get_node_str(const list_t *);
int delete_indexNode(list_t **, unsigned int);
void _freeList(list_t **);

/* for getlist.c */

size_t getLenght(const list_t *);
char **getStrings(list_t *);
size_t getList(const list_t *);
list_t *print_node(list_t *, char *, char);
ssize_t getNode(list_t *, list_t *);

/* for replaces.c */

int chain_delim(info_t *, char *, size_t *);
void chain_status(info_t *, char *, size_t *, size_t, size_t);
int alias_replacement(info_t *);
int var_replacement(info_t *);
int str_replacement(char **, char *);

#endif
