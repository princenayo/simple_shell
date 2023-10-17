#include "shell.h"

/**
 * _checkout - function that exits the shell
 * @stat: Structure containing potential arguments.
 *
 *  Return: given exit status (0) if info.argv[0] != "exit"
 */


int _checkout(info_t *stat)
{

	int check;

	if (stat->argv[1])
	{
		check = conv_string(stat->argv[1]);
		if (check == -1)
		{
			stat->status = 2;
			handle_error(stat, "Illegal number: ");
			print_input(stat->argv[1]);
			write_char('\n');

			return (1);
		}
		stat->err_num = conv_string(stat->argv[1]);
		return (-2);
	}
	stat->err_num = -1;
	return (-2);
}

/**
 * _change - function that changes the current directory.
 * @stat: Structure containing potential arguments.
 *
 *  Return: Always 0
 */

int _change(info_t *stat)
{
	char *str, *den, buffer[1024];
	int chdir_ret;

	str = getcwd(buffer, 1024);
		if (!str)
			string_input("TODO: >>getcwd failure emsg here<<\n");
	if (!stat->argv[1])
	{
		den = environ_var(stat, "HOME=");
		if (!den)
			chdir_ret =
				chdir((den = environ_var(stat, "PWD=")) ? den : "/");
		else
			chdir_ret = chdir(den);
	}
	else if (string_cmp(stat->argv[1], "-") == 0)
	{
		if (!environ_var(stat, "OLDPWD="))
		{
			string_input(str);
			put_char('\n');

			return (1);
		}
		string_input(environ_var(stat, "OLDPWD=")), put_char('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((den = environ_var(stat, "OLDPWD=")) ? den : "/");
	}
	else
		chdir_ret = chdir(stat->argv[1]);
	if (chdir_ret == -1)
	{
		handle_error(stat, "can't cd to ");
		print_input(stat->argv[1]), write_char('\n');
	}
	else
	{
		my_setenv(stat, "OLDPWD", environ_var(stat, "PWD="));
		my_setenv(stat, "PWD", getcwd(buffer, 1024));
	}
		return (0);
}

/**
 * _mylove - function that changes the current working directory.
 * @stat: Structure containing potential arguments.
 *  Return: 0
 */

int _mylove(info_t *stat)
{
	char **args;

	args = stat->argv;
	string_input("help call works. Function not yet implemented \n");
	if (0)
		string_input(*args);
	return (0);
}
