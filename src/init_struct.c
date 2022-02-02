#include "fdf.h"

void	ft_init_vars(t_vars *vars)
{
	vars->mesh_len = 10;
	vars->roll = 0.615;
	vars->yaw = -0.8;
	vars->zoom_rate = 1.0;
	vars->shift_x = 10;
	vars->shift_y = 10;
	ft_create_matrix(vars);
}
