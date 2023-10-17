#include "shell.h"

/**
 * interest - function that returns true if shell is in the interactive mode
 * @stat: structured address
 * Return: 1 if interactive mode, 0 otherwise
 */

int interest(stat_t *stat)
{
	return (isatty(STDIN_FILENO) && stat->readfd <= 2);
}

/**
 * for_checks - function that checks if character is a delimeter
 * @d: the character to be checked
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */

int for_checks(char d, char *delim)
{
	while (*delim)
		if (*delim++ == d)
			return (1);
	return (0);
}

/**
 *_alpha -function that  checks for alphabetic character
 *@d:  character to be inputed
 *Return: 1 if d is alphabetic, 0 otherwise
 */

int _alpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_convert - function that converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _convert(char *str)
{
	int j, set = 1, flag = 0, outcome;
	unsigned int input = 0;

	for (j = 0;  str[j] != '\0' && flag != 2; j++)
	{
		if (str[j] == '-')
			set *= -1;

		if (str[j] >= '0' && str[j] <= '9')
		{
			flag = 1;
			input *= 10;
			input += (str[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (set == -1)
		outcome = -input;
	else
		outcome = input;
	return (outcome);
}
