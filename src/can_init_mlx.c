#include "fdf.h"

bool	can_init_mlx(t_map_info *map)
{
	map->mlx = mlx_init();
	if (map->mlx == NULL)
	{
		delete_map(map);
		return (false);
	}
	map->win = mlx_new_window(map->mlx, WIDTH, HEIGHT, "fdf");
	if (map->win == NULL)
	{
		delete_map(map);
		mlx_destroy_display(map->mlx);
		free(map->mlx);
		return (false);
	}
	return (true);
}
