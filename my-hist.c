#include "shell.h"

/**
 * file_hist - function that gets the history file
 * @stat: argument struct
 * Return: the string containg hist file
 */

char *file_hist(stat_t *stat)
{
	char *buf, *rec;

	rec = environ_var(stat, "HOME=");
	if (!rec)
		return (NULL);

	buf = malloc(sizeof(char) * (str_len(rec) + str_len(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	string_cpy(buf, rec);
	string_concat(buf, "/");
	string_concat(buf, HIST_FILE);
	return (buf);
}

/**
 * create_hist - function that creates a file,
 *	 or appends to an existing file
 * @stat: the argument struct
 *
 * Return: 1 on success, otherwise -1
 */

int create_hist(stat_t *stat)
{
	ssize_t fd;
	char *file = file_hist(stat);
	list_t *node = NULL;

	if (!file)
		return (-1);
	fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(file);
	if (fd == -1)
		return (-1);
	for (node = stat->history; node; node = node->next)
	{
		print_fd(node->string, fd);
		write_fd('\n', fd);
	}
	write_fd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * _readHist - function that reads history from file
 * @stat: the argument struct
 *
 * Return: histcount on success, 0 otherwise
 */

int _readHist(stat_t *stat)
{
	int k, last = 0, linecount = 0;
	ssize_t fd, rdlen, numb = 0;
	struct stat st;
	char *buf = NULL, *file = file_hist(stat);

	if (!file)
		return (0);
	fd = open(file, O_RDONLY);
	free(file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		numb = st.st_size;
	if (numb < 2)
		return (0);
	buf = malloc(sizeof(char) * (numb + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, numb);
	buf[numb] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (k = 0; k < numb; k++)
		if (buf[k] == '\n')
		{
			buf[k] = 0;
			_buildHist(stat, buf + last, linecount++);

			last = k + 1;
		}
	if (last != k)
		_buildHist(stat, buf + last, linecount++);
	free(buf);
	stat->histcount = linecount;

	while (stat->histcount-- >= HIST_MAX)
	{
		delete_indexNode(&(stat->history), 0);
		history_renum(stat);
	}
	return (stat->histcount);
}

/**
 * _buildHist - function that adds entry to a history list
 * @stat: arguments struct.
 * @buf: buffer
 * @linecount: the history linecount,
 * Return: 0 always
 */

int _buildHist(stat_t *stat, char *buf, int linecount)
{
	list_t *node = NULL;

	if (stat->history)
		node = stat->history;
	_endNode(&node, buf, linecount);
	if (!stat->history)
		stat->history = node;
	return (0);
}

/**
 * history_renum - function that renumbers the history linked list
 * @stat: arguments struct
 * Return: histcount
 */

int history_renum(stat_t *stat)
{
	list_t *node = stat->history;
	int k = 0;

	while (node)
	{
		node->num = k++;
		node = node->next;
	}
	return (stat->histcount = k);
}
