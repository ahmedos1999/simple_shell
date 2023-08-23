#include "main.h"

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buff: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 **/
int build_history_list(info_t *info, char *buff, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_tail(&node, buff, linecount);
	if (!info->history)
		info->history = node;
	return (0);

}
/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 **/
char *get_history_file(info_t *info)
{
	char *buff, *directory;

	directory = get_env(info, "HOME=");
	if (!directory)
		return (NULL);
	buff = malloc(sizeof(char) *
			(str_len(directory) + str_len(HISTORY_OUTPUT) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	str_cpy(buff, directory);
	str_concat(buff, "/");
	str_concat(buff, HISTORY_OUTPUT);
return (buff);
}

/**
 * write_to_history - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 **/
int write_to_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		put_strfd(node->str, fd);
		put_fd('\n', fd);
	}
	put_fd(BUFF_FLUSH, fd);
	close(fd);
return (1);
}
/**
 * read_from_history - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 **/
int read_from_history(info_t *info)
{
	int i, last = 0, l_count = 0;
	ssize_t fd, rd_len, f_size = 0;
	struct stat st;
	char *buff = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);
	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		f_size = st.st_size;
	if (f_size < 2)
		return (0);
	buff = malloc(sizeof(char) * (f_size + 1));
	if (!buff)
		return (0);
	rd_len = read(fd, buff, f_size);
	buff[f_size] = 0;
	if (rd_len <= 0)
		return (free(buff), 0);
	close(fd);
	for (i = 0; i < f_size; i++)
		if (buff[i] == '\n')
		{
			buff[i] = 0;
			build_history_list(info, buff + last, l_count++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buff + last, l_count++);
	free(buff);
	info->histcount = l_count;
	while (info->histcount-- >= 4096)
		delete_node_at_index(&(info->history), 0);
	renum_hist(info);
	return (info->histcount);
}

/**
 * renum_hist - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 **/
int renum_hist(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
