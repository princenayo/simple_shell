#include "shell.h"

/**
 * free_pointer - a function that frees a pointer and NULLs the address
 * @addr: address of the pointer to free
 * Return: 1 if freed, otherwise 0.
 */

int free_pointer(void **addr)
{
	if (addr && *addr)
	{
		free(*addr);
		*addr = NULL;

		return (1);
	}
	return (0);
}
