#include "main.h"

/**
 * put_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 **/
int put_fd(char c, int fd)
{
	static int i;
	static char buff[W_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= W_BUFF_SIZE)
	{
		write(fd, buff, i);
	}
	if (c != BUFF_FLUSH)
		buff[i++] = c;
	return (1);
}

/**
 * _atoi - converts string into integers
 * @s: the string to be converted
 *
 * Return: the converted integer value
**/
int _atoi(char *s)
{
	int i, j, n, x;

	i = n = 0;
	x = 1;
	while ((s[i] < '0' || s[i] > '9') && (s[i] != '\0'))
	{
		if (s[i] == '-')
			x *= -1;
			i++;
	}
	j = i;
	while ((s[j] >= '0') && (s[j] <= '9'))
	{
		n = (n * 10) + x * ((s[j]) - '0');
		j++;
	}
return (n);
}

/**
 * put_strfd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
 **/
int put_strfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
