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
#define BUFF_FLUSH -1



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


void execmd(char **argv);
char *get_location(char *command);

/** Built In Commands **/
int change_dir(char **argv);
int _help(char **argv);
int my_exit(char **argv);
int (*check_builtn(char *string))(char **argv);

/*** Singly Linked Lists Functions ***/
list_t *new_node(list_t **head, const char *str, int num);
list_t *add_node_tail(list_t **head, const char *str, int num);
int delete_node_at_index(list_t **head, unsigned int index);

/*** Memory Functions***/
char *_mem_set(char *s, char b, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int freep(void **ptr);
void frees(char **pp);
void freel(list_t **head_ptr);

/*** String Functions ***/
char *_strconcat(char *dest, char *src);
char *string_cpy(char *dest, char *src);
char *string_dup(const char *str);
int _strcmp(char *s1, char *s2);
int _strlen(char *s);
void put_string(char *str);
int _putchar(char c);


#endif
