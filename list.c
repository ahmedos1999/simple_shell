#include "main.h"

/**
 * new_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 **/
list_t *new_node(list_t **head, const char *str, int num)
{
	list_t *new_head;
	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	_mem_set((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
return (new_head);
}

/**
 * add_node_tail - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 **/
list_t *add_node_tail(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	_mem_set((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}

	else
		*head = new_node;

return (new_node);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 **/
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
return (0);
}
/**
 * len_l - determines length of linked list
 * @head: pointer to first node
 *
 * Return: size of list
 **/
size_t len_l(const list_t *head)
{
	size_t i = 0;

	while (head)
	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * list_to_strings - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 **/
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = len_l(head), j;
	char **strings;
	char *str;

	if (!head || !i)
		return (NULL);
	strings = malloc(sizeof(char *) * (i + 1));
	if (!strings)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			{
				free(strings[j]);
			}
			free(strings);
			return (NULL);
		}
		str = str_cpy(str, node->str);
		strings[i] = str;
	}
	strings[i] = NULL;
	return (strings);
}
