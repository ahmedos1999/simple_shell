#include "main.h"

/**
 * env_list - populates environ linked list
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
int env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_tail(&node, environ[i], 0);
	info->env = node;
return (0);
}

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 **/
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}
return (info->environ);
}

/**
 * get_env - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @env_n: environ variable name
 *
 * Return: the value
 **/
char *get_env(info_t *info, const char *env_n)
{
	list_t *node = info->env;
	char *p;

	while (node)

	{
		p = start_s_with(node->str, env_n);
		if (p && *p)
		{
			return (p);
		}
		node = node->next;
	}
return (NULL);
}

/**
 * set_env - Initialize a new environment variable,
 * or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 **/
int set_env(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buff = malloc(str_len(var) + str_len(value) + 2);
	if (!buff)
		return (1);
	str_cpy(buff, var);
	str_concat(buff, "=");
	str_concat(buff, value);
	node = info->env;
	while (node)
	{
		p = start_s_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_tail(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
