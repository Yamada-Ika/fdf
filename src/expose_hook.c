#include "fdf.h"

int	expose_hook(t_map_info *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	display_map(map);
	return (0);
}
