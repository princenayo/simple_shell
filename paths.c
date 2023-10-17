#include "shell.h"

/**
 * det_exec -function that determines an executable command
 * @info: the info struct
 * @path: path to a file
 * Return: 1 if true, 0 otherwise
 */

int det_exec(stat_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * duplicate_chars - function that duplicates characters
 * @pStr: the PATH string
 * @startdex: starting index
 * @stopdex: stopping index
 * Return: address to new buffer
 */

char *duplicate_chars(char *pStr, int startdex, int stopdex)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = startdex; i < stopdex; i++)
		if (pStr[i] != ':')
			buf[k++] = pStr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * f_cmd_path -function that  finds this cmd in the PATH string
 * @stat: the infomation  struct
 * @pStr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */

char *f_cmd_path(stat_t *stat, char *pStr, char *cmd)
{
	int k = 0, position = 0;
	char *path;

	if (!pStr)
		return (NULL);
	if ((str_len(cmd) > 2) && check_string(cmd, "./"))
	{
		if (det_exec(stat, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pStr[k] || pStr[k] == ':')
		{
			path = duplicate_chars(pStr, position, k);
			if (!*path)
				string_concat(path, cmd);
			else
			{
				string_concat(path, "/");
				string_concat(path, cmd);
			}
			if (det_exec(stat, path))
				return (path);
			if (!pStr[k])
				break;
			position = k;
		}
		k++;
	}
	return (NULL);
}
