#include "fdf.h"

bool	can_init_mlx(t_map_info *map)
{
	map->mlx = mlx_init();
	if (map->mlx == NULL)
		return (false);
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "fdf");
	if (map->win == NULL)
	{
		mlx_destroy_display(map->mlx);
		return (false);
	}
	return (true);
}
