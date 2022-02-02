#include "fdf.h"

void	ft_draw_line(t_data *img, t_2dcord *cord, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	int		step;
	double	step_max;
	int		color_step;

	ft_trans_cord(cord, vars);
	if (ft_is_over_img_size(cord))
		return ;
	delta_x = cord->x1 - cord->x0;
	delta_y = cord->y1 - cord->y0;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	// color
	if (vars->color0 == 0)
		vars->color0 = 0xFFFFFF;
	if (vars->color1 == 0)
		vars->color1 = 0xFFFFFF;
	color_step = (vars->color1 - vars->color0) / step_max;
	step = 0;
	while (step < step_max)
	{
		cord->x0 += delta_x;
		cord->y0 += delta_y;
		my_mlx_pixel_put(img, cord->x0, cord->y0, vars->color0);
		vars->color0 += color_step;
		step++;
	}
}
