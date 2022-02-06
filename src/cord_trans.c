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

void	ft_trans_cord(t_map *map0, t_map *map1, t_vars *vars)
{
	ft_rotation(vars, &(map0->x), &(map0->y), &(map0->z));
	ft_rotation(vars, &(map1->x), &(map1->y), &(map1->z));
}
