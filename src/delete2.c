#include "fdf.h"

void	delete_all(t_map_info *map)
{
	mlx_destroy_image(map->mlx, map->img.img);
	delete_display(map);
	delete_map(map);
}
