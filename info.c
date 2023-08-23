#include "main.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 **/
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 **/
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_to_w(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;

			}
		}
		while (info->argv && info->argv[i])
			i++;
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 **/
void free_info(info_t *info, int all)
{
	frees(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freel(&(info->env));
		if (info->history)
			freel(&(info->history));
		if (info->alias)
			freel(&(info->alias));
		frees(info->environ);
		info->environ = NULL;
		freep((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		put_char(BUFF_FLUSH);
	}
}
