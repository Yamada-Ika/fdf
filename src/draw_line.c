#include "fdf.h"

static int	_get_color(int s_color, int e_color, int step, double step_max)
{
	int		diff[3];
	double	delta[3];
	int		color;

	diff[RED] = (((e_color >> 16) & 0xFF) - ((s_color >> 16) & 0xFF));
	diff[GREEN] = (((e_color >> 8) & 0xFF) - ((s_color >> 8) & 0xFF));
	diff[BLUE] = ((e_color & 0xFF) - (s_color & 0xFF));
	delta[RED] = diff[RED] / step_max;
	delta[GREEN] = diff[GREEN] / step_max;
	delta[BLUE] = diff[BLUE] / step_max;
	color = s_color
		+ ((int)(delta[RED] * step) << 16)
		+ ((int)(delta[GREEN] * step) << 8)
		+ (int)(delta[BLUE] * step);
	return (color);
}

static bool	_is_points_over_window(t_point *start, t_point *end)
{
	return (
		(start->x < 0.0 && end->x < 0.0)
		|| (start->y < 0.0 && end->y < 0.0)
		|| ((double)WIDTH < start->x && (double)WIDTH < end->x)
		|| ((double)HEIGHT < start->y && (double)HEIGHT < end->y)
	);
}

void	draw_line(t_image_info *img, t_point *start,
	t_point *end, double **matrix)
{
	double	delta_x;
	double	delta_y;
	double	step_max;
	int		step;

	trans_point(start, end, matrix);
	if (_is_points_over_window(start, end))
		return ;
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	step = 0;
	while (step < step_max)
	{
		put_pixel(img,
			start->x + delta_x * step,
			start->y + delta_y * step,
			_get_color(start->color, end->color, step, step_max));
		step++;
	}
}
