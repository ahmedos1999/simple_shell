#include "main.h"

/**get_node_index - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * print_list_string - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 **/
size_t print_list_string(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_str(h->str ? h->str : "(nil)");
		put_str("\n");
		h = h->next;
		i++;
	}
return (i);
}

/**
 * list_printer - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 **/
size_t list_printer(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		put_str(convert_number(h->num, 10, 0));
		put_char(':');
		put_char(' ');
		put_str(h->str ? h->str : "(nil)");
		put_str("\n");
		h = h->next;
		i++;
	}
return (i);
}

/**
 * node_starts_with - returns node whose string starts with start
 * @node: pointer to list head
 * @start: string to match
 * @c: the next character after start to match
 *
 * Return: match node or null
 **/
list_t *node_starts_with(list_t *node, char *start, char c)
{
	char *p = NULL;

	while (node)
	{
		p = start_s_with(node->str, start);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
			return (NULL);
}
