#include "stddef.h"

size_t	ft_get_line_size(char **s)
{
	size_t	size;

	size = 0;
	while (s[size] != NULL)
		size++;
	return (size);
}

size_t	get_map_column_size(char ***map)
{
	size_t	size;

	size = 0;
	while (map[0][size] != NULL)
		size++;
	return (size);
}

size_t	get_map_row_size(char ***map)
{
	size_t	size;

	size = 0;
	while (map[size] != NULL)
		size++;
	return (size);
}
