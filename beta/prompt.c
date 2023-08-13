#include "main.h"

int main(int argc, char **argv )
{
	char *prompt = "(Shell Beta) $ ";
	char *line_pointer, *line_pointer_cp, *token;
	size_t n = 0;
	ssize_t line_read;
	const char *delim = " \n";
	int i = 0, num_tokens = 0;
	(void)argc;

	/* Prompt Loop */
	while (1)
	{
		/* Print $ sign & Shell Name for prompt */
		printf("%s", prompt);
		line_read = getline(&line_pointer, &n, stdin);

		/** Exiting the Shell **/
		if (line_read == -1)
		{
			printf("Shell Out....\n");
			return (-1);
		}

		/* Allocating memory for line_pointer_cp in Heap */
		line_pointer_cp = malloc(sizeof(char) * line_read);
		if (line_pointer_cp == NULL)
		{
			perror("tsh: memory allocation error");
			return (-1);
		}

		/* Copying a string from line_pointer to line_pointer_cp */
		strcpy(line_pointer_cp, line_pointer);

		/* Counting Tokens */
		token = strtok(line_pointer_cp, delim);
		num_tokens++;
		while (token != NULL)
		{
			token = strtok(NULL, delim);
			num_tokens++;
		}

		/** Allocating memory in heap for ArgV  **/
		argv = malloc(sizeof(char *) * num_tokens);
		
		/** Tokenizing the string and store it in ArgV in Heap **/
		token = strtok(line_pointer_cp, delim);
		for (i = 0; token != NULL; i++)
		{
			argv[i] = malloc(sizeof(char) * strlen(token));
			strcpy(argv[i], token);
			token = strtok(NULL, delim);
		}
		argv[i] = NULL;

		/* Excute the command */
		execmd(argv);
	}
free(argv);
free(line_pointer);
free(line_pointer_cp);

return (0);
}
