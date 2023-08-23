#include "main.h"

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 **/
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	blt_n builtintable[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"cd", my_cd},
		{"history", my_history},
		{"setenv", my_set_env},
		{"unsetenv", my_unset_env},
		{"alias", my_alias},
		{NULL, NULL}
	};
	for (i = 0; builtintable[i].f; i++)
	{
		if (str_cmp(info->argv[0], builtintable[i].f) == 0)
		{
			info->line_count++;
			built_in_ret = builtintable[i].built_in(info);
			break;
		}
	}
return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 **/
void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	}
	if (!k)
		return;
	path = find_path(info, get_env(info, "PATH="), info->argv[0]);

	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * find_path - finds this cmd in the PATH string
 * @info: the info struct
 * @path_str: the PATH string
 * @cmd: the cmd to find
 *
 * Return: full path of cmd if found or NULL
 **/
char *find_path(info_t *info, char *path_str, char *cmd)
{
	int i = 0, c_pos = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((str_len(cmd) > 2) && start_s_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dup_chars(path_str, c_pos, i);
			if (!*path)
				str_concat(path, cmd);
			else
			{
				str_concat(path, "/");
				str_concat(path, cmd);
			}
			if (is_cmd(info, path))
			{
				return (path);
			}
			if (!path_str[i])
				break;
			c_pos = i;
		}
		i++;
	}
	return (NULL);
}
