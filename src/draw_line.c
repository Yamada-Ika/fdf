#include "fdf.h"

static int	_get_color(int start_color, int end_color, int step, int step_max)
{
	int		diff[3];
	double	delta[3];
	int		color;

	diff[RED] = (((end_color >> 16) & 0xFF) - ((start_color >> 16) & 0xFF));
	diff[GREEN] = (((end_color >> 8) & 0xFF) - ((start_color >> 8) & 0xFF));
	diff[BLUE] = ((end_color & 0xFF) - (start_color & 0xFF));
	delta[RED] = diff[RED] / (double)step_max;
	delta[GREEN] = diff[GREEN] / (double)step_max;
	delta[BLUE] = diff[BLUE] / (double)step_max;
	color = start_color + ((int)(delta[RED] * step) << 16) + ((int)(delta[GREEN] * step) << 8) + (int)(delta[BLUE] * step);
	return (color);
}

void	draw_line(t_image_info *img, t_point *start,
	t_point *end, double **matrix)
{
	double	delta_x;
	double	delta_y;
	double	step_max;
	int		step;

	trans_point(start, end, matrix);
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	step = 0;
	while (step < step_max)
	{
		put_pixel(img, start->x + delta_x * step,
			start->y + delta_y * step, _get_color(start->color, end->color, step, (int)step_max));
		step++;
	}
}
