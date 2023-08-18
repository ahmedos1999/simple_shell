#include "main.h"

/** Built_In Change Directory **/
int change_dir(char **argv)
{
	if (argv[1] == NULL)
		fprintf(stderr, "lsh: expected argument to \"cd\"\n");
	else
	{
		if (chdir(argv[1]) != 0)
		{
			perror("lsh");
		}
	}
return (1);
}

/** Built_In Help **/
int _help(char **argv)
{
	int i;
	char *built_in_cmnd[] = {"cd", "help", "exit"};
	size_t num_builtins = sizeof(built_in_cmnd);
	
	printf("Type program names and arguments, and hit enter.\n");
	printf("The following are built in:\n");
	for (i = 0; i < num_builtins; i++ )
	{
		printf("  %s\n", built_in_cmnd[i]);
	}
	printf("Use the man command for information on other programs.\n");
return (1);
}

/** Built_In Exit **/
int my_exit(char **argv)
{
	 return (0);
}
