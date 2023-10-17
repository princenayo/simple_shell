#include "shell.h"

/**
 * conv_string - function that  converts strings to integer numbers.
 * @str: string to be converted to integer
 *
 * Return: 0 if no numbers in string, converted number else
 *       -1 on error
 */

int conv_string(char *str)
{
	int k = 0;
	unsigned long int output = 0;

	if (*str == '+')
		str++;
	for (k = 0;  str[k] != '\0'; k++)
	{
		if (str[k] >= '0' && str[k] <= '9')
		{
			output *= 10;
			output += (str[k] - '0');
			if (output > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (output);
}

/**
 * handle_error - function that prints error messages
 * @stat: the parameter & return information  structure
 * @str: string retaining the specified error.
 * Return: 0 if no numbers is string, converted number else
 *        -1 on error
 */

void handle_error(info_t *stat, char *str)
{
	print_input(stat->fname);
	print_input(": ");
	pt_decimal(stat->line_count, STDERR_FILENO);
	print_input(": ");
	print_input(stat->argv[0]);
	print_input(": ");
	print_input(str);
}

/**
 * pt_decimal - prints a decimal integer
 * @n: the input argument
 * @sd: the filedescriptor to write to
 * Return: number of charactersto be printed
 */

int pt_decimal(int n, int sd)
{
	int (*__putchar)(char) = put_char;
	int k, numb = 0;
	unsigned int _abs_, lenght;

	if (sd == STDERR_FILENO)
		__putchar = write_char;
	if (n < 0)
	{
		_abs_ = -n;
		__putchar('-');

		numb++;
	}
	else
		_abs_ = n;
	lenght = _abs_;
	for (k = 1000000000; k > 1; k /= 10)
	{
		if (_abs_ / k)
		{
			__putchar('0' + lenght / k);
			numb++;
		}
		lenght %= k;
	}
	__putchar('0' + lenght);
	numb++;

	return (numb);
}

/**
 * conv_function - converter function to be used, a clone of itoa
 * @numb: number
 * @line: baseline
 * @flags: argument flags
 * Return: string
 */

char *conv_function(long int numb, int line, int flags)
{
	static char *arr;
	static char buffer[50];
	char sin = 0;
	char *p;
	unsigned long n = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		sin = '-';
	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do      {
		*--p = arr[n % line];
		n /= line;
	} while (n != 0);

	if (sin)
		*--p = sin;
	return (p);
}

/**
 * replace_hash - replaces first instance of '#' with '\0'
 * @str: pointer to the string to be modified
 *
 * Return: 0;
 */

void replace_hash(char *str)
{
	int k;

	for (k = 0; str[k] != '\0'; k++)
		if (str[k] == '#' && (!k || str[k - 1] == ' '))
		{
			str[k] = '\0';
			break;
		}
}
