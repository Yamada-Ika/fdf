#include "fdf.h"

bool	can_display_default_projection(t_map_info *map)
{
	map->zoom_rate = 150 * pow(map->row_size * map->col_size, -0.507);
	map->mouse_x = 0.0;
	map->mouse_y = 0.0;
	if (!can_display_map(map))
		return (false);
	map->shift_x = WIDTH / 3;
	map->shift_y = HEIGHT / 3 + 250;
	if (!can_redisplay_map(map))
		return (false);
	map->yaw = degree_to_radian(-45);
	if (!can_redisplay_map(map))
		return (false);
	map->roll = degree_to_radian(60);
	if (!can_redisplay_map(map))
		return (false);
	return (true);
}
