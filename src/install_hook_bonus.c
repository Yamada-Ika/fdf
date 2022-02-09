#include "fdf.h"

void	install_hook(t_map_info *map)
{
	mlx_key_hook(map->win, key_hook, map);
	mlx_mouse_hook(map->win, mouse_hook, map);
	mlx_expose_hook(map->win, expose_hook, map);
}
