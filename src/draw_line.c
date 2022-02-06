#include "fdf.h"

int	get_color_grad(int color_code0, int color_code1, double step)
{
	return ((color_code1 - color_code0) / step);
}

void	draw_line(t_image_info *img, t_point *map0,
	t_point *map1, double **matrix)
{
	double	delta_x;
	double	delta_y;
	int		step;
	double	step_max;
	int		color_grad;

	ft_trans_cord(map0, map1, matrix);
	delta_x = map1->x - map0->x;
	delta_y = map1->y - map0->y;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	color_grad = get_color_grad(map0->color, map1->color, step_max);
	step = 0;
	while (step < step_max)
	{
		my_mlx_pixel_put(img, map0->x + delta_x * step,
			map0->y + delta_y * step, map0->color + color_grad * step);
		step++;
	}
}
