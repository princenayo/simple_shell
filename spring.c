#include "shell.h"

/**
 * str_len -function that returns the length of a string
 * @str: the string whose length to check
 * Return: (k) length of string
 */

int str_len(char *str)

{
	int k = 0;

	if (!str)
		return (0);
	while (*str++)
		k++;
	return (k);
}

/**
 * string_cmp - function that compares two strings.
 * @str1: the first string
 * @str2: the second string to compare with str1
 * Return: negative if str1 < str2, positive if str1 > str2,
 *		 zero if str1 == str2
 */

int string_cmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * check_string - function that checks if the substring
 *			 starts with the main string
 * @str1: string to search
 * @str2: the substring to find
 * Return: pointer of next char of str1 or NULL
 */

char *check_string(const char *str1, const char *str2)
{
	while (*str2)
		if (*str2++ != *str1++)
			return (NULL);
	return ((char *)str1);
}

/**
 * string_concat - function that concatenates two strings
 * @dest_buff: the destination buffer
 * @src_buff: the source buffer
 * Return: pointer to destination buffer
 */

char *string_concat(char *dest_buff, char *src_buff)
{
	char *ptr = dest_buff;

	while (*dest_buff)
		dest_buff++;
	while (*src_buff)
		*dest_buff++ = *src_buff++;
	*dest_buff = *src_buff;
	return (ptr);
}
