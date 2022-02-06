#include "fdf.h"

size_t	get_strs_elem_size(char **strs)
{
	size_t	size;

	size = 0;
	while (strs[size] != NULL)
		size++;
	return (size);
}
