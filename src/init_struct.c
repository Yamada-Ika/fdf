#include "fdf.h"

bool	can_init_map_info(t_map_info *map)
{
	map->yaw = degree_to_radian(0);
	map->roll = degree_to_radian(0);
	map->pitch = degree_to_radian(0);
	map->zoom_rate = 1.0;
	map->shift_x = 0.0;
	map->shift_y = 0.0;
	map->mouse_x = 0.0;
	map->mouse_y = 0.0;
	return (can_new_matrix(map));
}
