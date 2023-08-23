#include "main.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 **/
int interactive(info_t *info)
{
		return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 **/
int is_delim(char c, char *delim)
{
	while (*delim)
	{
		if (*delim++ == c)
			return (1);
	}
			return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 **/

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_cmd - determines if a file is an executable command
 * @info: the info struct
 * @path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 **/
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @path_str: the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 **/
char *dup_chars(char *path_str, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (path_str[i] != ':')
			buff[k++] = path_str[i];
	buff[k] = 0;
	return (buff);
}
