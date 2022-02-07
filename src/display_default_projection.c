#include "fdf.h"

void	display_default_projection(t_map_info *map)
{
	map->zoom_rate = 10.0;
	map->shift_x = WIDTH / 3;
	map->shift_y = HEIGHT / 3;
	map->mouse_x = WIDTH / 3;
	map->mouse_y = HEIGHT / 3;
	display_map(map);
	mlx_destroy_image(map->mlx, map->img.img);
	mlx_clear_window(map->mlx, map->win);
	map->yaw = degree_to_radian(-45);
	display_map(map);
	mlx_destroy_image(map->mlx, map->img.img);
	mlx_clear_window(map->mlx, map->win);
	map->roll = degree_to_radian(50);
	display_map(map);
}
