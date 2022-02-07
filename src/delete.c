#include "fdf.h"

static void	_free_matrix(double **matrix)
{
	free(matrix[0]);
	free(matrix[1]);
	free(matrix[2]);
	free(matrix[3]);
	free(matrix);
}

static void	_delete_matrix(t_matrix mtx)
{
	_free_matrix(mtx.affine);
	_free_matrix(mtx.shift);
	_free_matrix(mtx.zoom);
	_free_matrix(mtx.move_cursor);
	_free_matrix(mtx.to_corner_for_zoom);
	_free_matrix(mtx.to_corner_for_rotate);
	_free_matrix(mtx.rotate_x);
	_free_matrix(mtx.rotate_y);
	_free_matrix(mtx.rotate_z);
	_free_matrix(mtx.move_map_origin);
	_free_matrix(mtx.tmp_mtx);
}

void	delete_points(t_point **points, size_t row_size)
{
	size_t	i;

	if (points == NULL)
		return ;
	i = 0;
	while (i < row_size)
	{
		free(points[i]);
		i++;
	}
	free(points);
}

void	delete_map(t_map_info *map)
{
	_delete_matrix(map->matrix);
	delete_points(map->points, map->row_size);
	delete_points(map->for_update, map->row_size);
}

void	delete_mlx(t_map_info *map)
{
	if (map->win != NULL)
		mlx_destroy_window(map->mlx, map->win);
	mlx_destroy_display(map->mlx);
	free(map->mlx);
}
