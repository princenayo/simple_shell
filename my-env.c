#include "shell.h"

/**
 * print_env - function that prints the current environment
 * @stat: Structure containing  arguments for the function prototype
 *
 * Return: Always 0
 */

int print_env(info_t *stat)
{
	get_node_str(stat->env);
	return (0);
}

/**
 * environ_var - function that determines the  value of an environ variable
 * @stat: Structure containing arguments for the function prototype
 * @nayo: environment variable name
 * Return: the value of env
 */

char *environ_var(info_t *stat, const char *nayo)
{
	list_t *node = stat->env;
	char *ptr;

	while (node)
	{
		ptr = check_string(node->string, nayo);
		if (ptr && *ptr)
			return (ptr);
		node = node->next;
	}
	return (NULL);
}

/**
 * init_env -function that  initializes a new environment variable
 * @stat: Structure containing arguments for the prototype function
 *
 * Return: 0 always
 */

int init_env(info_t *stat)
{
	if (stat->argc != 3)
	{
		print_input("Incorrect number of arguements\n");
		return (1);
	}
	if (my_setenv(stat, stat->argv[1], stat->argv[2]))
		return (0);
	return (1);
}

/**
 * remove_env - function that removes an environment variable
 * @stat: Structure containing arguments for the prototype function.
 *
 *  Return: 0 always
 */

int remove_env(info_t *stat)
{
	int k;

	if (stat->argc == 1)
	{
		print_input("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= stat->argc; k++)
		my_unsetenv(stat, stat->argv[k]);

	return (0);
}

/**
 * pop_env - function that populates env linked list
 * @stat: Structure containing arguments for the prototype function.
 *
 * Return: 0 always
 */

int pop_env(info_t *stat)
{
	list_t *node = NULL;
	size_t k;

	for (k = 0; environ[k]; k++)
		_endNode(&node, environ[k], 0);
	stat->env = node;
	return (0);
}
