#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	if (is_invalid_args(argc, argv))
		return (1);
	vars.map = ft_read_map(argv[1]);
	if (vars.map == NULL)
		return (1);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (1);
	ft_init_vars(&vars);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "fdf");
	ft_install_hook(&vars);
	ft_display_map(&vars);
	mlx_loop(vars.mlx);
}
