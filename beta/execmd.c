#include "main.h"

void execmd(char **argv)
{
	int i;
	char *command = NULL, *actual_command = NULL;
	int (*func_p)(char**);

	if (argv)
	{
		command = argv[0];
		func_p = check_builtn(command);


		actual_command = get_location(command);

		if (execve(actual_command, argv, NULL) == -1)
		{
			perror("Error: ");
		}

	}
}

int (*check_builtn(char *string))(char **argv)
{
	int i = 0;
	blt_n functions[] = {
		{"cd", change_dir},
		{"help", _help},
		{"exit", my_exit}
	};
	for (i = 0; i < 3; i++)
	{
		if (strcmp(string, functions[i].s) == 0)
		{
			return (functions[i].built_in);
		}
	}
return (0);
}
