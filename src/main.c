#include "fdf.h"

__attribute__((destructor))
void	check_leak(void)
{
	char	cmd[50];

	sprintf(cmd, "leaks %d", getpid());
	system(cmd);
}

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

int	main(int argc, char *argv[])
{
	t_map_info	map;

	if (is_invalid_args(argc, argv))
		return (1);
	if (!can_read_map(argv[1], &map))
		return (1);
	if (!can_init_map_info(&map))
		return (1);
	if (!can_init_mlx(&map))
		return (1);
	install_hook(&map);
	display_default_projection(&map);
	mlx_loop(map.mlx);
	delete_mlx(&map);
	delete_map(&map);
	return (0);
}
