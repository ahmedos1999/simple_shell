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

/*typedef struct binary_path
{
	char *bin_path;
	char *flags;
};*/

void execmd(char **argv);
char *get_location(char *command);

#endif
