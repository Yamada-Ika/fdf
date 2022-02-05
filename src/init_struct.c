#include "fdf.h"

void	ft_init_vars(t_vars *vars)
{
	vars->mesh_len = 10;
	vars->yaw = 0.0;
	vars->roll = 0.0;
	vars->pitch = 0.0;
	vars->zoom_rate = 1.0;
	vars->shift_x = 0;
	vars->shift_y = 0;
	ft_new_matrix(vars);
}
