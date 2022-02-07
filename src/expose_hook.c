#include "fdf.h"

int	expose_hook(t_map_info *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	if (!can_display_map(map))
		mlx_loop_end(map->mlx);
	return (0);
}
