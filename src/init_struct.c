#include "fdf.h"

void	init_map_info(t_map_info *map)
{
	map->yaw = 0.0;
	map->roll = 0.0;
	map->pitch = 0.0;
	map->zoom_rate = 1.0;
	map->shift_x = 0;
	map->shift_y = 0;
	map->mouse_x = 0.0;
	map->mouse_y = 0.0;
	ft_new_matrix(map);
}
