#include "fdf.h"

static double	**_new_matrix(void)
{
	double	**matrix;

	matrix = (double **)ft_calloc(4, sizeof(double *));
	matrix[0] = (double *)ft_calloc(4, sizeof(double));
	matrix[1] = (double *)ft_calloc(4, sizeof(double));
	matrix[2] = (double *)ft_calloc(4, sizeof(double));
	matrix[3] = (double *)ft_calloc(4, sizeof(double));
	set_unit_matrix(matrix);
	return (matrix);
}

void	ft_new_matrix(t_map_info *map)
{
	t_matrix	matrix;

	matrix.tmp_mtx = _new_matrix();
	matrix.to_corner_for_zoom = _new_matrix();
	matrix.to_corner_for_rotate = _new_matrix();
	matrix.move_map_origin = _new_matrix();
	matrix.move_cursor = _new_matrix();
	matrix.zoom = _new_matrix();
	matrix.rotate_x = _new_matrix();
	matrix.rotate_y = _new_matrix();
	matrix.rotate_z = _new_matrix();
	matrix.shift = _new_matrix();
	matrix.affine = _new_matrix();
	map->mtx = matrix;
}
