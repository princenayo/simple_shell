#include "shell.h"

/**
 **fill_memory- function that fills memory with a constant byte
 *@ptr: the address to the memory area
 *@byte: the byte to fill *ptr with
 *@num: the number of bytes to be filled
 *Return: (ptr) an address of the memory area.
 */

char *fill_memory(char *ptr, char byte, unsigned int num)
{
	unsigned int k;

	for (k = 0; k < num; k++)
		ptr[k] = byte;
	return (ptr);
}

/**
 * free_string - function that frees a string of strings
 * @ss: string of strings
 */

void free_string(char **ss)
{
	char **b = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
	free(b);
}

/**
 * memory_realloc - function that reallocates a block of memory
 * @addr: pointer to previous malloc'ated block
 * @fmr_size: byte size of former block
 * @curr_size: byte size of current block
 * Return: address to da old block nameen.
 */

void *memory_realloc(void *addr, unsigned int fmr_size, unsigned int curr_size)
{
	char *h;

	if (!addr)
		return (malloc(curr_size));
	if (!curr_size)
		return (free(addr), NULL);
	if (curr_size == fmr_size)
		return (addr);

	h = malloc(curr_size);
	if (!h)
		return (NULL);
	fmr_size = fmr_size < curr_size ? fmr_size : curr_size;
	while (fmr_size--)
		h[fmr_size] = ((char *)addr)[fmr_size];
	free(addr);
	return (h);
}
