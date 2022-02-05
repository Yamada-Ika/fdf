#include "fdf.h"

int	get_color_gradation(int color_code0, int color_code1, double step)
{
	return ((color_code1 - color_code0) / step);
}

void	ft_draw_line(t_data *img, t_2dcord *cord, t_vars *vars)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	int		color;
	int		step;
	double	step_max;
	int		color_gradation;

	ft_trans_cord(cord, vars);
	delta_x = cord->x1 - cord->x0;
	delta_y = cord->y1 - cord->y0;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	color_gradation = get_color_gradation(vars->color0, vars->color1, step_max);
	x = cord->x0;
	y = cord->y0;
	color = vars->color0;
	step = 0;
	while (step < step_max)
	{
		x += delta_x;
		y += delta_y;
		my_mlx_pixel_put(img, x, y, color);
		color += color_gradation;
		step++;
	}
}
