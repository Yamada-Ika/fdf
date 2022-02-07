#include "fdf.h"

static double	**_new_matrix(void)
{
	double	**matrix;

	matrix = (double **)ft_calloc(4, sizeof(double *));
	if (matrix == NULL)
		return (NULL);
	matrix[0] = (double *)ft_calloc(4, sizeof(double));
	if (matrix[0] == NULL)
		return (matrix);
	matrix[1] = (double *)ft_calloc(4, sizeof(double));
	if (matrix[1] == NULL)
		return (matrix);
	matrix[2] = (double *)ft_calloc(4, sizeof(double));
	if (matrix[2] == NULL)
		return (matrix);
	matrix[3] = (double *)ft_calloc(4, sizeof(double));
	if (matrix[3] == NULL)
		return (matrix);
	set_unit_matrix(matrix);
	return (matrix);
}

static bool	is_null_in_matrix(double **matrix)
{
	if (matrix == NULL)
		return (true);
	if (matrix[0] == NULL
		|| matrix[1] == NULL
		|| matrix[2] == NULL
		|| matrix[3] == NULL)
		return (true);
	else
		return (false);
}

static	bool	_is_invalid_matrix_in_t_matrix(t_matrix *mtx)
{
	if (is_null_in_matrix(mtx->affine)
		|| is_null_in_matrix(mtx->shift)
		|| is_null_in_matrix(mtx->zoom)
		|| is_null_in_matrix(mtx->move_cursor)
		|| is_null_in_matrix(mtx->to_corner_for_zoom)
		|| is_null_in_matrix(mtx->to_corner_for_rotate)
		|| is_null_in_matrix(mtx->rotate_x)
		|| is_null_in_matrix(mtx->rotate_y)
		|| is_null_in_matrix(mtx->rotate_z)
		|| is_null_in_matrix(mtx->move_map_origin)
		|| is_null_in_matrix(mtx->tmp_mtx))
		return (true);
	else
		return (false);
}

bool	can_new_matrix(t_map_info *map)
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
	map->matrix = matrix;
	if (_is_invalid_matrix_in_t_matrix(&(map->matrix)))
		return (false);
	return (true);
}
