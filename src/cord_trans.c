#include "fdf.h"

void	ft_rotation(t_vars *vars, double *x, double *y, double *z)
{
	double	prev_x;
	double	prev_y;
	double	prev_z;

	prev_x = *x;
	prev_y = *y;
	prev_z = *z;
	*x = (vars->affine_matrix[0][0] * prev_x
			+ vars->affine_matrix[0][1] * prev_y
			+ vars->affine_matrix[0][2] * prev_z
			+ vars->affine_matrix[0][3]);
	*y = (vars->affine_matrix[1][0] * prev_x
			+ vars->affine_matrix[1][1] * prev_y
			+ vars->affine_matrix[1][2] * prev_z
			+ vars->affine_matrix[1][3]);
}

void	ft_trans_cord(t_2dcord *cord, t_vars *vars)
{
	ft_rotation(vars, &(cord->x0), &(cord->y0), &(cord->z0));
	ft_rotation(vars, &(cord->x1), &(cord->y1), &(cord->z1));
}
