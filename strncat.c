#include "shell.h"

/**
 *my_strcpy - function that copies a string pointed by the source.
 *@dest: pointer to destination buffer
 *@src: pointer to source string
 *@num: the number of characters to be copied
 *Return: the pointer to destination buffer
 */

char *my_strcpy(char *dest, char *src, int num)
{
	int k, h;

	k = 0;
	while (src[k] != '\0' && k < num - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < num)
	{
		h = k;
		while (h < num)
		{
			dest[h] = '\0';
			h++;
		}
	}
	return (dest);
}

/**
 **my_strncat - function that concatenates two strings
 *@dest: pointer to destination buffer
 *@src: pointer to source string
 *@num: maximum number of bytes to be used
 *Return: pointer to destination buffer
 */

char *my_strncat(char *dest, char *src, int num)
{
	int k = 0, h = 0;

	while (dest[k] != '\0')
		k++;
	while (src[h] != '\0' && h < num)
	{
		dest[k] = src[h];
		k++;
		h++;
	}
	if (h < num)
		dest[k] = '\0';
	return (dest);
}

/**
 **my_strchr - function that  locates a character in a string
 *@str: pointer to the string to be parsed
 *@c: the character to be located
 *
 *Return: (str) a pointer to the first occurence of character
 */

char *my_strchr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
