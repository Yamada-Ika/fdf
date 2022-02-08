#include "fdf.h"

void	update_map_points(t_point **dst, t_point **src,
							size_t row_size, size_t col_size)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < row_size)
	{
		j = 0;
		while (j < col_size)
		{
			dst[i][j].x = src[i][j].x;
			dst[i][j].y = src[i][j].y;
			dst[i][j].z = src[i][j].z;
			j++;
		}
		i++;
	}
}
