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

	if (is_help_option(argc, argv))
		return (print_usage());
	if (is_invalid_args(argc, argv))
		return (print_error("Error: Invalid argument!"));
	if (!can_read_map(argv[1], &map))
		return (print_error("Error: Cannot read map!"));
	if (!can_init_map_info(&map))
		return (print_error("Error: Cannot initialize map!"));
	if (!can_init_mlx(&map))
		return (print_error("Error: Cannot initialize minilibx variables!"));
	if (!can_display_default_projection(&map))
	{
		delete_mlx(&map);
		delete_map(&map);
		return (print_error("Error: Cannot display map!"));
	}
	install_hook(&map);
	mlx_loop(map.mlx);
	delete_mlx(&map);
	delete_map(&map);
	return (0);
}
