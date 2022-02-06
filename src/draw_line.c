#include "fdf.h"

int	get_color_gradation(int color_code0, int color_code1, double step)
{
	return ((color_code1 - color_code0) / step);
}

void	ft_draw_line(t_data *img, t_map *map0, t_map *map1, double **matrix)
{
	double	delta_x;
	double	delta_y;
	double	x;
	double	y;
	int		color;
	int		step;
	double	step_max;
	int		color_gradation;

	ft_trans_cord(map0, map1, matrix);
	delta_x = map1->x - map0->x;
	delta_y = map1->y - map0->y;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	color_gradation = get_color_gradation(map0->color, map1->color, step_max);
	x = map0->x;
	y = map0->y;
	color = map0->color;
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
