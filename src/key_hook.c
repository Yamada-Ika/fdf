#include "fdf.h"

int	key_hook(int key, t_map_info *map)
{
	if (key == ESCAPE)
		mlx_loop_end(map->mlx);
	return (0);
}
