#include "fdf.h"

void	ft_create_matrix(t_vars *vars)
{
	vars->matrix = (double **)ft_calloc(4, sizeof(double *));
	vars->matrix[0] = (double *)ft_calloc(4, sizeof(double));
	vars->matrix[1] = (double *)ft_calloc(4, sizeof(double));
	vars->matrix[2] = (double *)ft_calloc(4, sizeof(double));
	vars->matrix[3] = (double *)ft_calloc(4, sizeof(double));
}

// |x'|   |cos(yaw) -sin(yaw)  0 Tx||x|
// |y'| = |sin(yaw) cos(yaw)  -1 Ty||y|
// |0 |   |0            0              0  0||z|
// |0 |   |0            0              0  0||1|
void	ft_set_matrix(t_vars *vars)
{
	vars->matrix[0][0] = cos(vars->yaw) * vars->zoom_rate;
	vars->matrix[0][1] = -sin(vars->yaw) * vars->zoom_rate;
	vars->matrix[0][3] = vars->shift_x * vars->zoom_rate;
	vars->matrix[1][0] = sin(vars->yaw) * sin(vars->roll) * vars->zoom_rate;
	vars->matrix[1][1] = cos(vars->yaw) * sin(vars->roll) * vars->zoom_rate;
	vars->matrix[1][2] = -1.0 * vars->zoom_rate;
	vars->matrix[1][3] = vars->shift_y * vars->zoom_rate;
}
