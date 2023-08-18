#include "main.h"

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 **/
ssize_t read_buffer(info_t *info, char *buff, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buff, R_BUFF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * line_input - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 **/
int line_input(info_t *info, char **ptr, size_t *length)
{
	static char buff[R_BUFF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buffer(info, buff, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = str_char(buff + i, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);
	if (s)
		str_nconcat(new_p, buff + i, k - i);
	else
		str_ncpy(new_p, buff + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
/**
 * signal_handler - blocks ctrl-C
 * @signal_num: the signal number
 *
 * Return: void
 **/
void signal_handler(__attribute__((unused))int signal_num)
{
	put_str("\n");
	put_str("$ ");
	put_char(BUFF_FLUSH);
}

/**
 * chain_buff - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 **/
ssize_t chain_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buff);
		*buff = NULL;
		signal(SIGINT, signal_handler);
#if USE_GETLINE
		r = getline(buff, &len_p, stdin);
#else
		r = line_input(info, buff, &len_p);
#endif
		if (r > 0)
		{
			if ((*buff)[r - 1] == '\n')
			{
				(*buff)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			build_history_list(info, *buff, info->histcount++);
			*len = r;
			info->cmd_buf = buff;
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 **/
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r = 0;
	char **p_buff = &(info->arg), *p;

	put_char(BUFF_FLUSH);
	r = chain_buff(info, &buff, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buff + i;
		check_chain(info, buff, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buff, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = 0;
		}
		*p_buff = p;
		return (str_len(p));

	}
	*p_buff = buff;
	return (r);
}
