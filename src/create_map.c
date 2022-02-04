#include "fdf.h"

t_map	**ft_create_map(size_t row_size, size_t column_size)
{
	t_map	**map;
	size_t	i;

	map = (t_map **)ft_calloc(row_size, sizeof(t_map *));
	i = 0;
	while (i < row_size)
	{
		map[i] = (t_map *)ft_calloc(column_size, sizeof(t_map));
		i++;
	}
	return (map);
}
