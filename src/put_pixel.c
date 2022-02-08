#include "fdf.h"

void	put_pixel(t_image_info *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || WIDTH - 1 < x || y < 0 || HEIGHT - 1 < y)
		return ;
	dst = data->addr + (y * data->line_len + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
