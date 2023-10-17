#include "shell.h"

/**
 * dsh - main function for  shell loop
 * @stat: the parameter & return info struct
 * @ds: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */

int dsh(stat_t *stat, char **ds)
{
	ssize_t k = 0;
	int builtin = 0;

	while (k != -1 && builtin != -2)
	{
		init_info(stat);
		if (interest(stat))
			string_input("$ ");
		write_char(BUF_FLUSH);
		k = getline_minus(stat);
		if (k != -1)
		{
			grab_info(stat, ds);
			builtin = cmd_builtin(stat);
			if (builtin == -1)
				get_cmd(stat);
		}
		else if (interest(stat))
			put_char('\n');
		info_freed(stat, 0);
	}
	create_hist(stat);
	info_freed(stat, 1);
	if (!interest(stat) && stat->status)
		exit(stat->status);
	if (builtin == -2)
	{
		if (stat->err_num == -1)
			exit(stat->status);
		exit(stat->err_num);
	}
	return (builtin);
}

/**
 * cmd_builtin - finds a builtin command
 * @stat: the parameter & return info struct
 * Return: -1 if builtin not found,
 *0 if builtin executed successfully,
 *1 if builtin found but not successful,
 *-2 if builtin signals exit()
 */

int cmd_builtin(stat_t *stat)
{
	int k, built_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _checkout},
		{"env", print_env},
		{"help", _mylove},
		{"history", ma_history},
		{"setenv", init_env},
		{"unsetenv", remove_env},
		{"cd", _change},
		{"alias", mic_alias},
		{NULL, NULL}
	};

	for (k = 0; builtintbl[k].type; k++)
		if (string_cmp(stat->argv[0], builtintbl[k].type) == 0)
		{
			stat->line_count++;
			built_ret = builtintbl[k].func(stat);
			break;
		}
	return (built_ret);
}

/**
 * get_cmd - function that finds a command in PATH
 * @stat: the parameter & return information structure
 * Return: 0
 */

void get_cmd(stat_t *stat)
{
	char *path = NULL;
	int j, h;

	stat->path = stat->argv[0];
	if (stat->linecount_flag == 1)
	{
		stat->line_count++;
		stat->linecount_flag = 0;
	}
	for (j = 0, h = 0; stat->arg[j]; j++)
		if (!for_checks(stat->arg[j], " \t\n"))
			h++;
	if (!h)
		return;
	path = f_cmd_path(stat, environ_var(stat, "PATH="), stat->argv[0]);
	if (path)
	{
		stat->path = path;
		_fork(stat);
	}
	else
	{
		if ((interest(stat) || environ_var(stat, "PATH=")
					|| stat->argv[0][0] == '/') && det_exec(stat, stat->argv[0]))
			_fork(stat);
		else if (*(stat->arg) != '\n')
		{
			stat->status = 127;
			handle_error(stat, "not found\n");
		}
	}
}

/**
 * _fork - function that forks  an exec thread to run cmd
 * @stat: the parameter & return info structure
 * Return: 0
 */

void _fork(stat_t *stat)
{
	pid_t cpid;

	cpid = fork();
	if (cpid == -1)
	{

		perror("Error:");
		return;
	}
	if (cpid == 0)
	{
		if (execve(stat->path, stat->argv, my_environ(stat)) == -1)
		{
			info_freed(stat, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}

	}
	else
	{
		wait(&(stat->status));
		if (WIFEXITED(stat->status))
		{
			stat->status = WEXITSTATUS(stat->status);
			if (stat->status == 126)
				handle_error(stat, "Permission denied\n");
		}
	}
}
