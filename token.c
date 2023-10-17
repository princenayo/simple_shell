#include "shell.h"

/**
 * **string_tok - function that splits a string into words
 * @str: the input string to be splited
 * @del: delimeter string
 *
 * Return: a pointer to array of strings, or NULL if failed
 */

char **string_tok(char *str, char *del)
{
	int i, j, k, m, string = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!del)
		del = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!for_checks(str[i], del) && (for_checks(str[i + 1], del) || !str[i + 1]))
			string++;
	if (string == 0)
		return (NULL);
	s = malloc((1 + string) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < string; j++)
	{
		while (for_checks(str[i], del))
			i++;
		k = 0;
		while (!for_checks(str[i + k], del) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)

				free(s[k]);

			free(s);

			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

/**
 * **string_split - function that splits a string into words
 * @str: input string to be splited
 * @del:  delimeter
 *
 * Return: an address to an array of strings, or NULL if failed
 */

char **string_split(char *str, char del)
{
	int i, j, k, m, string = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != del && str[i + 1] == del) ||
				(str[i] != del && !str[i + 1]) || str[i + 1] == del)
			string++;
	if (string == 0)
		return (NULL);
	s = malloc((1 + string) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < string; j++)
	{
		while (str[i] == del && str[i] != del)
			i++;
		k = 0;
		while (str[i + k] != del && str[i + k] && str[i + k] != del)
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}
