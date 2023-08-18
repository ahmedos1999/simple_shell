#include "main.h"

/**
 * freep - frees a pointer and NULLs the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int freep(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
return (0);
}

/**
 * frees - frees a string of strings
 * @pp: string of strings
 **/
void frees(char **pp)
{
	char **a = pp;

	if (!a)
		return;

	while (*a)
		free(*a++);

	free(a);
}

/**
 * freel - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 **/
void freel(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
*head_ptr = NULL;
}
