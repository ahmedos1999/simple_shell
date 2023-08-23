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

/**
 * replace_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					str_dup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					str_dup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					str_dup(str_char(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], str_dup(""));
	}
return (0);
}
/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
return (1);
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 **/
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = str_char(node->str, '=');
		if (!p)
			return (0);
		p = str_dup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
return (1);
}
