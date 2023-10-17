#include "shell.h"

/**
 * main - entry point
 * @argc: argument count
 * @argv: argument vector
 * Return: 0 on success, 1 on error
 */

int main(int argc, char **argv)
{
	stat_t stat[] = { STAT_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				print_input(argv[0]);
				print_input(": 0: Can't open ");

				print_input(argv[1]);

				write_char('\n');

				write_char(BUF_FLUSH);

				exit(127);
			}
			return (EXIT_FAILURE);
		}
		stat->readfd = fd;
	}
	pop_env(stat);
	_readHist(stat);
	dsh(stat, argv);
	return (EXIT_SUCCESS);
}
