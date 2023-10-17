#include "shell.h"

/**
 * ma_history -function that  displays the history list.
 * @stat: Structure containing potential arguments.
 *  Return: 0
 */

int ma_history(stat_t *stat)
{
	getList(stat->history);
	return (0);
}

/**
 * ma_alias - function that sets alias to string
 * @stat: constant function argument
 * @string: this is string alias
 *
 * Return: 0 on success, 1 on error
 */

int ma_alias(stat_t *stat, char *string)
{
	char *ptr, b;
	int den;

	ptr = my_strchr(string, '=');
	if (!ptr)
		return (1);
	b = *ptr;
	*ptr = 0;
	den = delete_indexNode(&(stat->alias),
			getNode(stat->alias, print_node(stat->alias, string, -1)));
	*ptr = b;
	return (den);
}

/**
 * get_alias - function that sets alias to string
 * @stat: constant function argument
 * @string: this is string alias
 *
 * Return: 0 on success, 1 on error
 */

int get_alias(stat_t *stat, char *string)
{
	char *ptr;

	ptr = my_strchr(string, '=');
	if (!ptr)
		return (1);
	if (!*++ptr)
		return (ma_alias(stat, string));

	ma_alias(stat, string);
	return (_endNode(&(stat->alias), string, 0) == NULL);
}

/**
 * pt_alias -function that prints an alias string
 * @list: the alias node
 *
 * Return: 0 on success, 1 on error
 */

int pt_alias(list_t *list)
{
	char *ptr = NULL, *b = NULL;

	if (list)
	{
		ptr = my_strchr(list->string, '=');
		for (b = list->string; b <= ptr; b++)
			put_char(*b);
		put_char('\'');
		string_input(ptr + 1);
		string_input("'\n");
		return (0);
	}
	return (1);
}

/**
 * mic_alias -function that  mimics the alias builtin.
 * @stat: constant function argument.
 *
 *  Return: 0
 */

int mic_alias(stat_t *stat)
{
	int k = 0;
	char *ptr = NULL;
	list_t *list = NULL;

	if (stat->argc == 1)
	{
		list = stat->alias;
		while (list)
		{
			pt_alias(list);
			list = list->next;
		}
		return (0);
	}
	for (k = 1; stat->argv[k]; k++)
	{
		ptr = my_strchr(stat->argv[k], '=');
		if (ptr)
			get_alias(stat, stat->argv[k]);
		else
			pt_alias(print_node(stat->alias, stat->argv[k], '='));
	}
	return (0);
}
