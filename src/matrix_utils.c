#include "fdf.h"

void	ft_create_affine_matrix(t_vars *vars)
{
	vars->affine_matrix = (double **)ft_calloc(4, sizeof(double *));
	vars->affine_matrix[0] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[1] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[2] = (double *)ft_calloc(4, sizeof(double));
	vars->affine_matrix[3] = (double *)ft_calloc(4, sizeof(double));
}

// |x'|   |cos(z_angle) -sin(z_angle)  0 Tx||x|
// |y'| = |sin(z_angle) cos(z_angle)  -1 Ty||y|
// |0 |   |0            0              0  0||z|
// |0 |   |0            0              0  0||1|
void	ft_set_affine_matrix(t_vars *vars)
{
	vars->affine_matrix[0][0] = cos(vars->z_angle) * vars->zoom_rate;
	vars->affine_matrix[0][1] = -sin(vars->z_angle) * vars->zoom_rate;
	vars->affine_matrix[0][3] = vars->shift_x * vars->zoom_rate;
	vars->affine_matrix[1][0] = sin(vars->z_angle) * sin(vars->x_angle) * vars->zoom_rate;
	vars->affine_matrix[1][1] = cos(vars->z_angle) * sin(vars->x_angle) * vars->zoom_rate;
	vars->affine_matrix[1][2] = -1.0 * vars->zoom_rate;
	vars->affine_matrix[1][3] = vars->shift_y * vars->zoom_rate;
}
