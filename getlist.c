#include "shell.h"

/**
 * getLenght - function that determines len of singly linked list
 * @head: pointer to first node
 * Return: size of a linked list
 */

size_t getLenght(const list_t *head)
{
	size_t k = 0;

	while (head)
	{
		head = head->next;
		k++;
	}
	return (k);
}

/**
 * getStrings - func that returns an array of strings of the list
 * @head: pointer to first node
 * Return: array of strings
 */

char **getStrings(list_t *head)
{
	list_t *node = head;
	size_t k = getLenght(head), j;
	char **strings;
	char *str;

	if (!head || !k)
		return (NULL);

	strings = malloc(sizeof(char *) * (k + 1));
	if (!strings)
		return (NULL);


	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(str_len(node->string) + 1);
		if (!str)
		{
			for (j = 0; j < k; j++)
				free(strings[j]);
			free(strings);
			return (NULL);
		}
		str = string_cpy(str, node->string);
		strings[k] = str;
	}
	strings[k] = NULL;
	return (strings);
}

/**
 * getList - func that prints all elements of a linked list
 * @head: address to the first node
 * Return: size of list
 */

size_t getList(const list_t *head)
{
	size_t k = 0;

	while (head)
	{
		string_input(conv_function(head->num, 10, 0));
		put_char(':');
		put_char(' ');
		string_input(head->string ? head->string : "(nil)");
		string_input("\n");
		head = head->next;
		k++;
	}
	return (k);
}

/**
 * print_node - returns node whose string starts with prefix
 * @node: pointer to list head
 * @pref: string to match
 * @d: the next character after prefix to match
 * Return: match node or null
 */

list_t *print_node(list_t *node, char *pref, char d)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = check_string(node->string, pref);
		if (ptr && ((d == -1) || (*ptr == d)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * getNode - function that  gets the index of a node in a list
 * @head: address to list head
 * @node: address to the node
 * Return: index of node or -1
 */

ssize_t getNode(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
