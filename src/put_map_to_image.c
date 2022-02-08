#include "fdf.h"

static void	_set_tmp_points_for_draw(t_point *tmp_points,
	t_point **points, size_t i, size_t j)
{
	tmp_points->x = points[i][j].x;
	tmp_points->y = points[i][j].y;
	tmp_points->z = points[i][j].z;
	tmp_points->color = points[i][j].color;
}

static void	_set_tmp_map_for_update(t_point **points_for_update,
	size_t i, size_t j, t_point *tmp_points)
{
	points_for_update[i][j].x = tmp_points->x;
	points_for_update[i][j].y = tmp_points->y;
	points_for_update[i][j].z = tmp_points->z;
	points_for_update[i][j].color = tmp_points->color;
}

static void	_draw_horizontal_line(t_map_info *map,
	t_point points[2], size_t i, size_t j)
{
	_set_tmp_points_for_draw(&(points[0]), map->points, i, j);
	_set_tmp_points_for_draw(&(points[1]), map->points, i, j + 1);
	draw_line(&(map->img), &points[0], &points[1], map->matrix.affine);
	_set_tmp_map_for_update(map->for_update, i, j, &(points[0]));
	_set_tmp_map_for_update(map->for_update, i, j + 1, &(points[1]));
}

static void	_draw_vertical_line(t_map_info *map,
	t_point points[2], size_t i, size_t j)
{
	_set_tmp_points_for_draw(&(points[0]), map->points, i, j);
	_set_tmp_points_for_draw(&(points[1]), map->points, i + 1, j);
	draw_line(&(map->img), &points[0], &points[1], map->matrix.affine);
	_set_tmp_map_for_update(map->for_update, i, j, &(points[0]));
	_set_tmp_map_for_update(map->for_update, i + 1, j, &(points[1]));
}

void	put_map_to_image(t_map_info *map)
{
	size_t	i;
	size_t	j;
	t_point	point_for_draw[2];

	i = 0;
	while (i < map->row_size)
	{
		j = 0;
		while (true)
		{
			if (j + 1 < map->col_size)
				_draw_horizontal_line(map, point_for_draw, i, j);
			if (i + 1 < map->row_size)
				_draw_vertical_line(map, point_for_draw, i, j);
			if (j + 1 == map->col_size)
				break ;
			j++;
		}
		i++;
	}
}
