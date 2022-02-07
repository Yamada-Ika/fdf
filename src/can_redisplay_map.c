#include "fdf.h"

bool	can_redisplay_map(t_map_info *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	mlx_clear_window(map->mlx, map->win);
	if (!can_display_map(map))
		return (false);
	else
		return (true);
}
