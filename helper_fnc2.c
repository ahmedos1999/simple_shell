#include "main.h"

/**
 * start_s_with - checks if needle starts with haystack
 * @hay_stack: string to search
 * @ndl: the substring to find
 *
 * Return: address of next char of haystack or NULL
 **/
char *start_s_with(const char *hay_stack, const char *ndl)
{
	while (*ndl)
	{
		if (*ndl++ != *hay_stack++)
			return (NULL);
	}
	return ((char *)hay_stack);
}
