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

#define W_BUFF_SIZE 1024
#define R_BUFF_SIZE 1024
#define BUFF_FLUSH -1

#define USE_GETLINE 0




extern char **environ;

/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 **/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}list_t;


/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * 	allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline containing arguements
 * @argv: an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 **/
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
}info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}


/**
 * struct builtin - contains a builtin string and related function
 * @f: the builtin command flag
 * @built_in: the function to be called
 **/
typedef struct builtin
{
	char *f;
	int (*built_in)(info_t *);
}blt_n;

/**** Main ****/
int simple_shell(info_t *, char **);
void fork_cmd(info_t *);

/*** Chain ***/
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t , size_t );
ssize_t chain_buff(info_t *, char **, size_t *);

/*** Find ***/
int find_builtin(info_t *);
void find_cmd(info_t *);
char *find_path(info_t *, char *, char *);

/*** Helpers ***/
int interactive(info_t *);
int is_delim(char , char *);
int _isalpha(int );
int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *start_s_with(const char *, const char *);

/*** Environ Functions ***/
int env_list(info_t *);
char **get_environ(info_t *);
char *get_env(info_t *, const char *);
int set_env(info_t *, char *, char *);

/** Built In Commands **/
int my_exit(info_t *);
int my_exit2(info_t *);
int my_help(info_t *);
int my_cd(info_t *);
int change_dir(info_t *info);

/*** INPUT  ***/
ssize_t read_buffer(info_t *, char *, size_t *);
int line_input(info_t *, char **, size_t *);
void signal_handler(__attribute__((unused))int );
ssize_t get_input(info_t *);

/*** Info Struct Initialization Functions ***/
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/*** Singly Linked Lists Functions ***/
list_t *new_node(list_t **, const char *, int);
list_t *add_node_tail(list_t **, const char *, int);
int delete_node_at_index(list_t **, unsigned int);
size_t len_l(const list_t *);
char **list_to_strings(list_t *);

/*** Memory Functions ***/
char *_mem_set(char *, char, unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
int freep(void **);
void frees(char **);
void freel(list_t **);

/*** String Functions ***/
char *str_concat(char *, char *);
char *str_nconcat(char *, char *, int);
char *str_cpy(char *, char *);
char *str_ncpy(char *, char *, int);
char *str_dup(const char *);
int str_cmp(char *, char *);
int str_len(char *);
char *str_char(char *, char);
void put_str(char *);
int put_strfd(char *, int);
int put_char(char);
int put_fd(char, int);
int _atoi(char *s);

/*** Tokenizing Functions ***/
char **str_to_w(char *, char *);
char **str_to_w2(char *, char );

/*** History Functions ***/
int build_history_list(info_t *, char *, int);


#endif
