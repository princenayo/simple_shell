#include "shell.h"

/**
 * init_info - function that initializes the struct
 * @stat: pointer to the struct
 * return: void
 */

void init_info(info_t *stat)
{
	stat->argv = NULL;
	stat->arg = NULL;
	stat->path = NULL;
	stat->argc = 0;
}

/**
 * grab_info - function that initializes the struct
 * @stat: pointer to the struct
 * @argv: argument vector
 */

void grab_info(info_t *stat, char **argv)
{
	int k = 0;

	stat->fname = argv[0];
	if (stat->arg)
	{
		stat->argv = string_tok(stat->arg, " \t");
		if (!stat->argv)
		{
			stat->argv = malloc(sizeof(char *) * 2);
			if (stat->argv)
			{
				stat->argv[0] = string_dup(stat->arg);
				stat->argv[1] = NULL;
			}
		}
		for (k = 0; stat->argv && stat->argv[k]; k++)
			;
		stat->argc = k;
		alias_replacement(stat);
		var_replacement(stat);
	}
}

/**
 * info_freed - function that frees struct fields
 * @stat: pointer to the struct
 * @n: let it be true if freeing all fields
 */

void info_freed(info_t *stat, int n)
{
	free_string(stat->argv);
	stat->argv = NULL;
	stat->path = NULL;
	if (n)
	{
		if (!stat->cmd_buf)
			free(stat->arg);
		if (stat->env)
			_freeList(&(stat->env));
		if (stat->history)
			_freeList(&(stat->history));
		if (stat->alias)
			_freeList(&(stat->alias));
		free_string(stat->environ);
		stat->environ = NULL;
		free_pointer((void **)stat->cmd_buf);
		if (stat->readfd > 2)
			close(stat->readfd);
		put_char(BUF_FLUSH);
	}
}
