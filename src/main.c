#include "fdf.h"

// __attribute__((destructor))
// void	check_leak(void)
// {
// 	char	cmd[50];

// 	sprintf(cmd, "leaks %d", getpid());
// 	system(cmd);
// }

int	main(int argc, char *argv[])
{
	t_map_info	map;

	if (is_invalid_args(argc, argv))
		return (1);
	if (!can_read_map(argv[1], &map))
		return (1);
	map.mlx = mlx_init();
	if (map.mlx == NULL)
		return (1);
	map.win = mlx_new_window(map.mlx, WIDTH, HEIGHT, "fdf");
	if (map.win == NULL)
	{
		mlx_destroy_display(map.mlx);
		return (1);
	}
	init_map_info(&map);
	install_hook(&map);
	display_map(&map);
	mlx_loop(map.mlx);
	mlx_destroy_display(map.mlx);
	free(map.mlx);
	return (0);
}
