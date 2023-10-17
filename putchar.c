#include "shell.h"

/**
 * string_cpy - function that copies a string
 * @str1: the destination string
 * @str2: the source string
 * Return: address to destination string
 */

char *string_cpy(char *str1, char *str2)
{
	int k = 0;

	if (str1 == str2 || str2 == 0)
		return (str1);
	while (str2[k])
	{
		str1[k] = str2[k];
		k++;
	}
	str1[k] = 0;
	return (str1);
}

/**
 * string_dup - function that duplicates a string
 * @strd: the string to be duplicated
 * Return: address to the duplicated string
 */

char *string_dup(const char *strd)
{
	int count = 0;
	char *ptr;

	if (strd == NULL)
		return (NULL);
	while (*strd++)
		count++;
	ptr = malloc(sizeof(char) * (count + 1));
	if (!ptr)
		return (NULL);
	for (count++; count--;)
		ptr[count] = *--strd;
	return (ptr);
}

/**
 *string_input - function that prints an input string
 *@strp: the string to be printed
 * Return: void
 */

void string_input(char *strp)
{
	int k = 0;

	if (!strp)
		return;
	while (strp[k] != '\0')
	{
		put_char(strp[k]);
		k++;
	}
}

/**
 * put_char - function that writes the character c to stdout
 * @c: The character to be printed
 *
 * Return: On success 1, on error, -1 is returned.
 */

int put_char(char c)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(1, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}
