#include "mlx.h"
#include <stdio.h>

#define ESCAPE 0xff1b
#define WIDTH 480
#define HEIGHT 480

typedef struct s_vars
{
	void	*mlx;
	void	*win;
}	t_vars;

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESCAPE)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return (0);
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Hello world!");
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop(vars.mlx);
}
