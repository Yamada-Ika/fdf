#include "fdf.h"

t_point	**create_points(size_t row_size, size_t col_size)
{
	t_point	**map;
	size_t	i;

	errno = 0;
	map = (t_point **)ft_calloc(row_size, sizeof(t_point *));
	if (map == NULL)
		return (NULL);
	i = 0;
	while (i < row_size)
	{
		errno = 0;
		map[i] = (t_point *)ft_calloc(col_size, sizeof(t_point));
		if (map[i] == NULL)
		{
			delete_points(map, i);
			return (NULL);
		}
		i++;
	}
	return (map);
}
