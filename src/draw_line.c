#include "fdf.h"

static int	_get_delta_color(int start_color, int end_color, int step)
{
	int	diff_r;
	int	diff_g;
	int	diff_b;
	int	delta;

	diff_r = (((end_color >> 16) & 0xFF) - ((start_color >> 16) & 0xFF));
	diff_g = (((end_color >> 8) & 0xFF) - ((start_color >> 8) & 0xFF));
	diff_b = ((end_color & 0xFF) - (start_color & 0xFF));
	delta = (diff_r / step) << 16;
	delta += (diff_g / step) << 8;
	delta += diff_b / step;
	return (delta);
}

static int	_get_color(int start_color, int delta_color, int step)
{
	return (start_color
		+ ((((delta_color >> 16) & 0xFF) * step) << 16)
		+ ((((delta_color >> 8) & 0xFF) * step) << 8)
		+ ((delta_color) & 0xFF) * step);
}

void	draw_line(t_image_info *img, t_point *start,
	t_point *end, double **matrix)
{
	double	delta_x;
	double	delta_y;
	int		delta_color;
	double	step_max;
	int		step;

	trans_point(start, end, matrix);
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	step_max = ft_max(ft_abs(delta_x), ft_abs(delta_y));
	delta_x /= step_max;
	delta_y /= step_max;
	delta_color = _get_delta_color(start->color, end->color, (int)step_max);
	step = 0;
	while (step < step_max)
	{
		put_pixel(img, start->x + delta_x * step,
			start->y + delta_y * step, _get_color(start->color, delta_color, step));
		step += 1;
	}
}
