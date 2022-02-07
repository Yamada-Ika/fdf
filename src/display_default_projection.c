#include "fdf.h"

bool	can_display_default_projection(t_map_info *map)
{
	map->zoom_rate = 255 * pow(map->row_size * map->col_size, -0.507);
	map->shift_x = WIDTH / 3;
	map->shift_y = HEIGHT / 3;
	map->mouse_x = WIDTH / 3;
	map->mouse_y = HEIGHT / 3;
	if (!can_display_map(map))
		return (false);
	map->yaw = degree_to_radian(-45);
	if (!can_redisplay_map(map))
		return (false);
	map->roll = degree_to_radian(50);
	if (!can_redisplay_map(map))
		return (false);
	return (true);
}
