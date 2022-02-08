#include "fdf.h"

bool	can_redisplay_map(t_map_info *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	if (can_display_map(map))
		return (true);
	else
		return (false);
}
