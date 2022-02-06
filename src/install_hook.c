#include "fdf.h"

void	ft_install_hook(t_map_info *map)
{
	mlx_key_hook(map->win, ft_key_hook, map);
	mlx_mouse_hook(map->win, ft_mouse_hook, map);
}
