#include "main.h"

/**
 * put_str - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 **/
void put_str(char *s)
{
	int i = 0;

	if (!s)
		return;
	while (s[i] != '\0')
	{
		put_char(s[i]);
		i++;
	}
}

/**
 * put_char - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 **/
int put_char(char c)
{
	static int i;
	static char buf[W_BUFF_SIZE];

	if (c == BUFF_FLUSH || i >= W_BUFF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUFF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * str_ncpy - copies a string
 * @dest: the destination string to be copied to
 * @src: the source string
 * @n: the amount of characters to be copied
 * Return: the concatenated string
 **/
char *str_ncpy(char *dest, char *src, int n)
{
	int i = 0, j;
	char *s = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
return (s);
}

/**
 * str_nconcat - concatenates two strings
 * @dest: the first string
 * @src: the second string
 * @n: the amount of bytes to be maximally used
 * Return: the concatenated string
 **/
char *str_nconcat(char *dest, char *src, int n)
{
	int i = 0, j = 0;
	char *s = dest;

	while (dest[i] != '\0')
		i++;

	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
return (s);
}

/**
 * str_char - locates a character in a string
 * @s: the string to be parsed
 * @c: the character to look for
 * Return: (s) a pointer to the memory area s
 **/
char *str_char(char *s, char c)
{
	do {
		if (*s == c)
			return (s);

	} while (*s++ != '\0');

return (NULL);
}
