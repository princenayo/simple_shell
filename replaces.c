#include "shell.h"

/**
 * chain_delim - function that tests if current char is a chained delimeter
 * @stat: argument struct
 * @buf: the char buffer
 * @ptr: pointer to current position in buf
 * Return: 1 if chain delimeter, 0 otherwise
 */

int chain_delim(stat_t *stat, char *buf, size_t *ptr)
{
	size_t h = *ptr;

	if (buf[h] == '|' && buf[h + 1] == '|')
	{
		buf[h] = 0;
		h++;
		stat->cmd_buf_type = CMD_OR;
	}
	else if (buf[h] == '&' && buf[h + 1] == '&')
	{
		buf[h] = 0;
		h++;
		stat->cmd_buf_type = CMD_AND;
	}
	else if (buf[h] == ';')
	{
		buf[h] = 0;
		stat->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = h;
	return (1);
}

/**
 * chain_status - function that checks chaining based on last status
 * @stat: the argument struct
 * @buf: the char buffer
 * @ptr: pointer to current location in buf
 * @n: length of buf
 * @k: size of buf
 * Return: Void
 */

void chain_status(stat_t *stat, char *buf, size_t *ptr, size_t k, size_t n)
{
	size_t h = *ptr;

	if (stat->cmd_buf_type == CMD_AND)
	{
		if (stat->status)
		{
			buf[k] = 0;
			h = n;
		}
	}
	if (stat->cmd_buf_type == CMD_OR)
	{
		if (!stat->status)
		{
			buf[k] = 0;
			h = n;
		}
	}
	*ptr = h;
}

/**
 * alias_replacement - function that replaces an aliases in a tokenized string
 * @stat: the argument struct
 * Return: 1 if replaced, else 0
 */

int alias_replacement(stat_t *stat)
{

	list_t *node;
	 char *ptr;
	 int k;

	for (k = 0; k < 10; k++)
	{
		node = print_node(stat->alias, stat->argv[0], '=');
		if (!node)
			return (0);
		free(stat->argv[0]);
		ptr = my_strchr(node->string, '=');
		if (!ptr)
			return (0);
		ptr = string_dup(ptr + 1);
		if (!ptr)
			return (0);
		stat->argv[0] = ptr;
	}
	return (1);
}

/**
 * var_replacement - function that replaces variable in the tokenized string
 * @stat: the argument struct
 *
 * Return: 1 if replaced, 0 otherwise
 */

int var_replacement(stat_t *stat)
{
	int k = 0;
	list_t *node;

	for (k = 0; stat->argv[k]; k++)
	{
		if (stat->argv[k][0] != '$' || !stat->argv[k][1])
			continue;
		if (!string_cmp(stat->argv[k], "$?"))
		{
			str_replacement(&(stat->argv[k]),
					string_dup(conv_function(stat->status, 10, 0)));
			continue;
		}
		if (!string_cmp(stat->argv[k], "$$"))
		{
			str_replacement(&(stat->argv[k]),
					string_dup(conv_function(getpid(), 10, 0)));
			continue;
		}
		node = print_node(stat->env, &stat->argv[k][1], '=');
		if (node)
		{
			str_replacement(&(stat->argv[k]),
					string_dup(my_strchr(node->string, '=') + 1));
			continue;
		}
		str_replacement(&stat->argv[k], string_dup(""));
	}
	return (0);
}

/**
 * str_replacement -function that  replaces string
 * @ptr: pointer to old string
 * @new: new string
 * Return: 1 if replaced, else 0
 */

int str_replacement(char **ptr, char *new)
{
	free(*ptr);
	*ptr = new;
	return (1);
}
