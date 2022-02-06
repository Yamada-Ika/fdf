#include "fdf.h"

static void	_update_map_points(t_point **dst, t_point **src, size_t row_size, size_t col_size)
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
			dst[i][j].color = src[i][j].color;
			j++;
		}
		i++;
	}
}

static void	_set_tmp_points_for_draw(t_point *tmp_points, t_point **points, size_t i, size_t j)
{
	tmp_points->x = points[i][j].x;
	tmp_points->y = points[i][j].y;
	tmp_points->z = points[i][j].z;
	tmp_points->color = points[i][j].color;
}

static void	_set_tmp_map_for_update(t_point **points_tmp_for_update, size_t i, size_t j, t_point *tmp_points)
{
	points_tmp_for_update[i][j].x = tmp_points->x;
	points_tmp_for_update[i][j].y = tmp_points->y;
	points_tmp_for_update[i][j].z = tmp_points->z;
	points_tmp_for_update[i][j].color = tmp_points->color;
}

void	ft_put_map_to_image(t_image_info *img, t_map_info *map)
{
	size_t	i;
	size_t	j;
	t_point	tmp_for_draw[2];

	i = 0;
	while (i < map->row_size)
	{
		j = 0;
		while (true)
		{
			if (j + 1 < map->column_size)
			{
				_set_tmp_points_for_draw(&(tmp_for_draw[0]), map->points, i, j);
				_set_tmp_points_for_draw(&(tmp_for_draw[1]), map->points, i, j + 1);
				draw_line(img, &tmp_for_draw[0], &tmp_for_draw[1], map->mtx.affine);
				_set_tmp_map_for_update(map->tmp_for_update, i, j, &(tmp_for_draw[0]));
				_set_tmp_map_for_update(map->tmp_for_update, i, j + 1, &(tmp_for_draw[1]));
			}
			if (i + 1 < map->row_size)
			{
				_set_tmp_points_for_draw(&(tmp_for_draw[0]), map->points, i, j);
				_set_tmp_points_for_draw(&(tmp_for_draw[1]), map->points, i + 1, j);
				draw_line(img, &tmp_for_draw[0], &tmp_for_draw[1], map->mtx.affine);
				_set_tmp_map_for_update(map->tmp_for_update, i, j, &(tmp_for_draw[0]));
				_set_tmp_map_for_update(map->tmp_for_update, i + 1, j, &(tmp_for_draw[1]));
			}
			if (j + 1 == map->column_size)
				break ;
			j++;
		}
		i++;
	}
	_update_map_points(map->points, map->tmp_for_update, map->row_size, map->column_size);
}
