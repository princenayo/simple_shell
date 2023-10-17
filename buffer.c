#include "shell.h"

/**
 * chain_buf -function that chains buffer commands
 * @stat: argument struct
 * @buf: pointer to the  buffer
 * @lenght: pointer to the  lenght variable
 * Return: bytes read
 */

ssize_t chain_buf(info_t *stat, char **buf, size_t *lenght)
{
	ssize_t p = 0;
	size_t width = 0;

	if (!*lenght)
	{

		free(*buf);
		*buf = NULL;
		signal(SIGINT, call_signal);
#if USE_GETLINE
		p = getline(buf, &width, stdin);
#else
		p = next_line(stat, buf, &width);
#endif
		if (p > 0)
		{
			if ((*buf)[p - 1] == '\n')
			{
				(*buf)[p - 1] = '\0';
				p--;
			}
			stat->linecount_flag = 1;
			replace_hash(*buf);
			_buildHist(stat, *buf, stat->histcount++);


			{
				*lenght = p;
				stat->cmd_buf = buf;
			}
		}
	}
	return (p);
}

/**
 * getline_minus -function that gets a line minus the newline
 * @stat: argument struct
 *
 * Return: bytes read
 */

ssize_t getline_minus(info_t *stat)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(stat->arg), *p;

	put_char(BUF_FLUSH);
	r = chain_buf(stat, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		chain_status(stat, buf, &j, i, len);
		while (j < len)
		{
			if (chain_delim(stat, buf, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			stat->cmd_buf_type = CMD_NORM;
		}
		*buf_p = p;
		return (str_len(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * rd_buffer - function that  reads a buffer
 * @stat: argument struct
 * @buf: buffer
 * @k: size
 * Return: r
 */

ssize_t rd_buffer(info_t *stat, char *buf, size_t *k)
{
	ssize_t p = 0;

	if (*k)
		return (0);
	p = read(stat->readfd, buf, READ_BUF_SIZE);
	if (p >= 0)
		*k = p;
	return (p);
}

/**
 * next_line - function that gets the next line of input from STDIN
 * @stat: argument struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @count: size of preallocated ptr buffer if not NULL
 * Return: s
 */

int next_line(info_t *stat, char **ptr, size_t *count)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *newp = NULL, *c;

	p = *ptr;
	if (p && count)
		s = *count;
	if (i == len)
		i = len = 0;
	r = rd_buffer(stat, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = my_strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	newp = memory_realloc(p, s, s ? s + k : k + 1);
	if (!newp) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		my_strncat(newp, buf + i, k - i);
	else
		my_strcpy(newp, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = newp;

	if (count)
		*count = s;
	*ptr = p;
	return (s);
}

/**
 * call_signal- blocks ctrl-C
 * @num: the signal number
 *
 * Return: 0
 */

void call_signal(__attribute__((unused))int num)
{
	string_input("\n");
	string_input("$ ");
	put_char(BUF_FLUSH);
}
