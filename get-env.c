#include "shell.h"

/**
 * my_environ - returns the string array copy of our environ
 * @stat: constant argument
 *
 * Return: 0
 */

char **my_environ(info_t *stat)
{
	if (!stat->environ || stat->env_changed)
	{
		stat->environ = getStrings(stat->env);
		stat->env_changed = 0;
	}
	return (stat->environ);
}

/**
 * my_unsetenv - function that remove an environment variable
 * @stat: Structure containing  constant argument
 *  Return: 1 on delete, otherwise 0
 * @den: the string env var property
 */

int my_unsetenv(info_t *stat, char *den)
{
	list_t *list = stat->env;
	size_t k = 0;
	char *ptr;

	if (!list || !den)
		return (0);

	while (list)
	{
		ptr = check_string(list->string, den);
		if (ptr && *ptr == '=')
		{
			stat->env_changed = delete_indexNode(&(stat->env), k);
			k = 0;
			list = stat->env;
			continue;
		}
		list = list->next;
		k++;
	}
	return (stat->env_changed);
}

/**
 * my_setenv - function that initialize a new environment variable,
 * @stat: Structure containing constant function argument
 * @den: the string env variable property
 * @data: the string env variable value
 *  Return: Always 0
 */

int my_setenv(info_t *stat, char *den, char *data)
{
	char *buf = NULL;
	list_t *list;
	char *ptr;

	if (!den || !data)
		return (0);

	buf = malloc(str_len(den) + str_len(data) + 2);
	if (!buf)
		return (1);
	string_cpy(buf, den);
	string_concat(buf, "=");
	string_concat(buf, data);
	list = stat->env;
	while (den)
	{
		ptr = check_string(list->string, den);
		if (ptr && *ptr == '=')
		{
			free(list->string);
			list->string = buf;
			stat->env_changed = 1;

			return (0);
		}
		list = list->next;
	}
	_endNode(&(stat->env), buf, 0);
	free(buf);
	stat->env_changed = 1;
	return (0);
}
