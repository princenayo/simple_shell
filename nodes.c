#include "shell.h"

/**
 * nodeAdd - function that adds a node at the beginning of the list
 * @h:  pointer to head node
 * @string: string field of nodes
 * @num: node index of the list
 * Return: size list
 */

list_t *nodeAdd(list_t **h, const char *string, int num)
{
	list_t *newNode;

	if (!h)
		return (NULL);
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	fill_memory((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (string)
	{
		newNode->string = string_dup(string);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
		newNode->next = *h;
		*h = newNode;
	}
	return (newNode);
}

/**
 * _endNode - function that adds a node at the end of the list
 * @h:  pointer to head node
 * @string: string field of node
 * @num: node index of the list
 * Return: size of list
 */

list_t *_endNode(list_t **h, const char *string, int num)
{
	list_t *newNode, *node;

	if (!h)
		return (NULL);

	node = *h;
	newNode = malloc(sizeof(list_t));
	if (!newNode)
		return (NULL);
	fill_memory((void *)newNode, 0, sizeof(list_t));
	newNode->num = num;
	if (string)
	{
		newNode->string = string_dup(string);
		if (!newNode->string)
		{
			free(newNode);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newNode;
	}
	else
		*h = newNode;
	return (newNode);
}

/**
 * get_node_str - func that  prints string element of a  linked list
 * @h: address to first node
 * Return: size of list
 */

size_t get_node_str(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		string_input(h->string ? h->string : "(nil)");
		string_input("\n");
		h = h->next;
		k++;
	}
	return (k);
}

/**
 * delete_indexNode - function that  deletes node at given index
 * @h: pointer to first node
 * @indx: index of node to delete
 * Return: 1 on success, 0 on failure
 */

int delete_indexNode(list_t **h, unsigned int indx)
{
	list_t *node, *oldNode;
	unsigned int k = 0;

	if (!h || !*h)
		return (0);

	if (!indx)
	{
		node = *h;
		*h = (*h)->next;
		free(node->string);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (k == indx)
		{
			oldNode->next = node->next;
			free(node->string);
			free(node);
			return (1);
		}
		k++;
		oldNode = node;
		node = node->next;
	}
	return (0);
}

/**
 * _freeList - function that frees the list
 * @h: address of pointer to head node
 * Return: void
 */

void _freeList(list_t **h)
{
	list_t *node, *nextNode, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		nextNode = node->next;
		free(node->string);
		free(node);
		node = nextNode;
	}
	*h = NULL;
}
