#include "main.h"

/**
 * str_len - returns the length of a string
 * @s: the string whose length to check
 *
 * Return: integer length of string
 **/
int str_len(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	
	while (*s++)
		i++;
	return (i);
}

/**
 * str_cmp - performs lexicogarphic comparison of two strangs.
 * @s1: the first strang
 * @s2: the second strang
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 **/
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);

		s1++;
		s2++;

	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * str_concat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 **/
char *str_concat(char *dest, char *src)
{
	char *temp = dest;

	while (*dest)
		dest++;

	while (*src)
		*dest++ = *src++;

	*dest = *src;
	return (temp);
}

/**
 * str_cpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 **/
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_dup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 **/
char *str_dup(const char *str)
{
	int str_l = 0;
	char *temp;

	if (str == NULL)
		return (NULL);

	while (*str++)
		str_l++;
	
	temp = malloc(sizeof(char) * (str_l + 1));
	if (!temp)
		return (NULL);

	for (str_l++; str_l--;)
		temp[str_l] = *--str;
	return (temp);
}
