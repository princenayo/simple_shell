#include "shell.h"

/**
 *print_input - function that  prints an input string
 * @string: the string pointer to be printed
 *
 * Return: void
 */

void print_input(char *string)
{
	int k = 0;

	if (!string)
		return;
	while (string[k] != '\0')
	{
		write_char(string[k]);
		k++;
	}
}

/**
 * write_char - function writes the character c to stderr
 * @c: The character to be printed
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */

int write_char(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(2, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 * write_fd - function that writes the character c to given fd
 * @c: The character to be printed
 * @fd: The file descriptor to write
 *
 * Return: On success 1.
 *	 On error, -1 is returned.
 */

int write_fd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 *print_fd - function that prints an input string
 * @string: the string pointer to be printed
 * @fd: filedescriptor to write.
 *
 * Return: the number of character to print
 */

int print_fd(char *string, int fd)
{
	int k = 0;

	if (!string)
		return (0);
	while (*string)
	{
		k += write_fd(*string++, fd);
	}
	return (k);
}
