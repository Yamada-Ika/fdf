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

void	ft_new_matrix(t_vars *vars)
{
	vars->tmp_for_product = _new_matrix();
	vars->to_upleftcorner_for_zoom_matrix = _new_matrix();
	vars->to_upleftcorner_for_rotate_matrix = _new_matrix();
	vars->to_map_origin_for_rotate_matrix = _new_matrix();
	vars->to_map_origin_for_zoom_matrix = _new_matrix();
	vars->zoom_matrix = _new_matrix();
	vars->rotate_x_matrix = _new_matrix();
	vars->rotate_y_matrix = _new_matrix();
	vars->rotate_z_matrix = _new_matrix();
	vars->shift_matrix = _new_matrix();
	vars->affine_matrix = _new_matrix();
}
